/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#define GRAPH_VAR
#define GS_VAR
#include "graphics.h"
#include "../event_graphic_port.h"


void Tgraphic_loop(void){
	struct timespec Lstart, Lfinish;
	double Lelapsed;

	pthread_mutex_lock(&Tlock_cubes);
	pthread_mutex_unlock(&Tlock_cubes);
	
	Ginit_ground();
	
	while(!EGSgame_exit){
		clock_gettime(CLOCK_MONOTONIC, &Lstart);

		//~ Gcube_grid();
		Gmove_camera();
		Gdisplay_objects();

		clock_gettime(CLOCK_MONOTONIC, &Lfinish);
		Lelapsed = (Lfinish.tv_sec - Lstart.tv_sec)*1000000;
		Lelapsed += (Lfinish.tv_nsec - Lstart.tv_nsec) / 1000.0;
		if(((1000000.0f/(float)config.screen_fps_limit)-Lelapsed)>0){
			usleep((1000000.0f/(float)config.screen_fps_limit)-Lelapsed);
		} else {
			printf("Your graphic thread is %f usec too slow\n",((1000000.0f/(float)config.screen_fps_limit)-Lelapsed));
		}
	}
}

void Gdraw_ground(){
	glCallList(Gground);
}

void Gcube_grid(void){
	if(	Gprerenderedcubes[0]==0){
		Gprerenderedcubes[0]=glGenLists(1);

		glNewList(Gprerenderedcubes[0], GL_COMPILE);

		int x;
		pthread_mutex_lock(&Tlock_cubes);
		for(x=0;x<16*16*16;x++){
			if(EGScubes[0][x]==0) continue; //Air
			Gdraw_block((x%16), ((x/16)%16), ((x/256)%16), (EGScubes[0][x]-1));
		}
		pthread_mutex_unlock(&Tlock_cubes);
		glEndList();
	} else {
		glCallList(Gprerenderedcubes[0]);
	}
}


/** \brief This function swaps the graphic buffer */
void Gdisplay_objects(void){
	SDL_GL_SwapBuffers();
}


/** \brief This function moves the gl coordsystem => it moves the EGplayer */
void Gmove_camera(void){
	static int Ldaynightlast;
	

	pthread_mutex_lock(&Tlock_input);

	if(Ldaynightlast!=EGday){
	if(EGday==0){
		float Lfogcol[3]={0.8f, 0.8f, 1.0f};
		glFogfv(GL_FOG_COLOR, Lfogcol);
		glFogf(GL_FOG_DENSITY, 0.05f);
		glClearColor(0.8f,0.8f,1.0f,0.0f);
	} else if(EGday==1) {
		float Lfogcol[3]={0.0f, 0.0f, 0.0f};
		glFogfv(GL_FOG_COLOR, Lfogcol);
		glFogf(GL_FOG_DENSITY, 1.5f);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	} else if(EGday==2) {
		float Lfogcol[3]={0.0f, 0.0f, 0.0f};
		glFogfv(GL_FOG_COLOR, Lfogcol);
		glFogf(GL_FOG_DENSITY, 0.5f);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	}
	Ldaynightlast=EGday;
	}

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(EGplayer.look[0], 1.0f, 0.0f, 0.0f);
	glRotatef(EGplayer.look[1], 0.0f, 1.0f, 0.0f);


	glTranslatef(
	-(EGplayer.pos_abs[0]-=EGplayer.move_speed*EGinput.v_move_rel[0]),
	-((EGplayer.pos_abs[1]-=DEFAULT_MOVESPEED*EGinput.v_move_rel[1])+EGplayer.height),
	-((EGplayer.pos_abs[2]-=EGplayer.move_speed*EGinput.v_move_rel[2])));
	
	if(EGplayer.pos_abs[1]<0){
		glTranslatef(0,EGplayer.pos_abs[1],0);
		printf("x:%f y:%f z:%f xrot:%f yrot:%f\r", EGplayer.pos_abs[0], EGplayer.pos_abs[1], EGplayer.pos_abs[2], EGplayer.look[0], EGplayer.look[1]);
		EGplayer.jump=0;
		EGplayer.pos_abs[1]=0;
	}
	
	EGinput.v_move_rel[0]=0;
	EGinput.v_move_rel[1]=0;
	EGinput.v_move_rel[2]=0;

	glTranslatef((int)EGplayer.pos_abs[0],0,(int)EGplayer.pos_abs[2]);
	Gdraw_ground();
	glTranslatef(-(int)EGplayer.pos_abs[0],0,-(int)EGplayer.pos_abs[2]);

	pthread_mutex_unlock(&Tlock_input);
}


/** \brief This function draws a block
 * 	\param float 	x position of the block
 * 	\param float 	y position of the block
 * 	\param float 	z position of the block
*/
void Gdraw_block(float x, float y, float z, int texture){
	glBindTexture(GL_TEXTURE_2D, BlockTextures[texture][0][0]);
	glBegin(GL_QUADS);

	// Back Face
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f(x+0.0f, y+0.0f, z+1.0f);
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f(x+1.0f, y+0.0f, z+1.0f);
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f(x+1.0f, y+1.0f, z+1.0f);
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f(x+0.0f, y+1.0f, z+1.0f);

	// Front Face
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f(x+0.0f, y+0.0f, z+0.0f);
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f(x+0.0f, y+1.0f, z+0.0f);
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f(x+1.0f, y+1.0f, z+0.0f);
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f(x+1.0f, y+0.0f, z+0.0f);

	// Top Face
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f(x+0.0f, y+1.0f, z+0.0f);
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f(x+0.0f, y+1.0f, z+1.0f);
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f(x+1.0f, y+1.0f, z+1.0f);
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f(x+1.0f, y+1.0f, z+0.0f);

	// Bottom Face
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f(x+0.0f, y+0.0f, z+0.0f);
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f(x+1.0f, y+0.0f, z+0.0f);
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f(x+1.0f, y+0.0f, z+1.0f);
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f(x+0.0f, y+0.0f, z+1.0f);

	// Right face
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f(x+1.0f, y+0.0f, z+0.0f);
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f(x+1.0f, y+1.0f, z+0.0f);
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f(x+1.0f, y+1.0f, z+1.0f);
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f(x+1.0f, y+0.0f, z+1.0f);

	// Left Face
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f(x+0.0f, y+0.0f, z+0.0f);
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f(x+0.0f, y+0.0f, z+1.0f);
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f(x+0.0f, y+1.0f, z+1.0f);
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f(x+0.0f, y+1.0f, z+0.0f);

	glEnd();
}
