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


#include "graphics.h"
#include "../cubebox.h"

/** \brief Frees SDL memory */
void quit(void){
	SDL_CloseAudio();
	SDL_Quit();
	exit(0);
}

void Ginit_ground(){
	int x,z;
	Gground=glGenLists(1);
	glNewList(Gground, GL_COMPILE);

	glBindTexture( GL_TEXTURE_2D, BlockTextures[0][0][0]);
	glBegin(GL_QUADS);
	
	for(x=-50;x<=50;x++)
	for(z=-50;z<=50;z++){
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f(x+0.0f, 0.0f, z+0.0f);
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f(x+0.0f, 0.0f, z+1.0f);
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f(x+1.0f, 0.0f, z+1.0f);
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f(x+1.0f, 0.0f, z+0.0f);
	}

	glEnd();

	glEndList();
}

/** \brief Open a GL window */
void Iinit_screen(void){
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0){
		printf("Error initializing SDL\n");
		SDL_Quit();
		return;
	}
	
	SDL_putenv("SDL_VIDEO_CENTERED=center");


	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	SDL_SetVideoMode(config.screen_width, config.screen_height, config.screen_bpp, SDL_FLAGS);
	
	float ratio=(float)(config.screen_width/config.screen_height)+0.09f;
	glViewport(0, 0, config.screen_width, config.screen_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0f, ratio, 0.1f, 50.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DOUBLEBUFFER);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

	float Lfogcol[3]={0.8f, 0.8f, 1.0f};
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, Lfogcol);
	glFogf(GL_FOG_MODE, GL_EXP);
    glFogf(GL_FOG_DENSITY, 0.05f);

	glShadeModel(GL_SMOOTH);
	glClearColor(0.8f,0.8f,1.0f,0.0f);
	glClearDepth(1.0f);

	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_GrabInput(SDL_GRAB_ON);
	atexit(quit);
}


/** \brief load textures into BlockTextures */
void Iload_block_textures(void){
	SDL_Surface *TextureImage;
	int i,j,k;
	char s[BLOCKTEXTURESRCLEN+BLOCKTEXTURESNAMELEN+20];
	strncpy(s, blocktexturesrc, (BLOCKTEXTURESRCLEN+BLOCKTEXTURESNAMELEN+20));
	
	char buf[strlen(blocktexturesrc)+strlen(BLOCKTEXTURESNAME)+20];
// Copy texturepack string into blocktexturesrc
	strncpy(blocktexturesrc, config.texturepack, BLOCKTEXTURESRCLEN);

	for(i=0;i<BLOCKTEXTURESNUM;i++)
	for(j=0;j<BLOCKSUBTEXTURES;j++)
	for(k=0;k<BLOCKSIDES;k++){
		strcpy(s, blocktexturesrc);
		sprintf(buf, BLOCKTEXTURESNAME, i, j, k);
		strcat(s, buf);
		TextureImage = SDL_LoadBMP(s);

		if(!TextureImage){
			printf("Failed to load: '%s'\n", s);
			exit(2);
		} else {
			printf("Loaded: '%s'\n", s);
		}

		glGenTextures(BLOCKSIDES, &BlockTextures[i][j][k]);
		glBindTexture( GL_TEXTURE_2D, BlockTextures[i][j][k] );

		glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage->w,
			TextureImage->h, 0, GL_BGR,
			GL_UNSIGNED_BYTE, TextureImage->pixels );

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		SDL_FreeSurface(TextureImage);
	}
}

