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


#include "events.h"
#include "../event_graphic_port.h"

/** \brief Calculate the movement and movement speed */
void Emove_player(){
	int f=0;
	float x=0, y=0, z=0; // To send what really changed

	pthread_mutex_lock(&Tlock_input);
	x = EGinput.v_move_rel[0];
	y = EGinput.v_move_rel[2];
	z = EGinput.v_move_rel[1];
	
	
	// Limit view
	if(EGplayer.look[0]>90) EGplayer.look[0]=90;
	if(EGplayer.look[0]<-90)EGplayer.look[0]=-90;

	// WASD to move EGplayer
	if(EGinput.PressedKeys[SDLK_w]){
		EGinput.v_move_rel[0]-=sin(EGplayer.look[1]*M_PI/180);
		EGinput.v_move_rel[2]+=cos(EGplayer.look[1]*M_PI/180);
		f++;
	}
	if(EGinput.PressedKeys[SDLK_s]){
		EGinput.v_move_rel[0]+=sin(EGplayer.look[1]*M_PI/180)*0.9;
		EGinput.v_move_rel[2]-=cos(EGplayer.look[1]*M_PI/180)/0.9;
		f++;
	}
	if(EGinput.PressedKeys[SDLK_a]){
		EGinput.v_move_rel[0]+=(cos(EGplayer.look[1]*M_PI/180)*0.75);
		EGinput.v_move_rel[2]+=(sin(EGplayer.look[1]*M_PI/180)*0.75);
		f++;
	}
	if(EGinput.PressedKeys[SDLK_d]){
		EGinput.v_move_rel[0]-=(cos(EGplayer.look[1]*M_PI/180)*0.75);
		EGinput.v_move_rel[2]-=(sin(EGplayer.look[1]*M_PI/180)*0.75);
		f++;
	}

	//diagonal move limitation
	if(f==2){
		EGinput.v_move_rel[0]*=0.8;
		EGinput.v_move_rel[2]*=0.8;
	}

	//jump
	if(EGplayer.jump > 1){
		if(EGplayer.jump==19){
			EPlayEnvironmentSound(SND_JUMP, 1);			
		}
		EGinput.v_move_rel[1]-=4;
		
		EGplayer.jump--;
	}
	
	//crouch
	if(EGinput.PressedKeys[SDLK_LCTRL]&& EGplayer.jump==0){
		EGplayer.height=PLAYER_HEIGHT*0.6;
	}
	
	// Movespeed
	if(((EGinput.v_move_rel[0]+EGinput.v_move_rel[2])>0.001)||((EGinput.v_move_rel[0]+EGinput.v_move_rel[2])<-0.001)){
		if(EGplayer.jump==0){
		if(!EGinput.PressedKeys[SDLK_LCTRL]){
			if(EGinput.PressedKeys[SDLK_LSHIFT]){ //sprint
				EGplayer.move_speed = 2*DEFAULT_MOVESPEED;
				EPlayEnvironmentSound(SND_RUN, 0);
			} else { //walk
				EGplayer.move_speed = DEFAULT_MOVESPEED;
				EPlayEnvironmentSound(SND_WALK, 0);				
			}
		} else { //crouch
			EGplayer.move_speed  = DEFAULT_MOVESPEED*0.5;
			EPlayEnvironmentSound(SND_WALK, 0);				
		}
	} else { //jump
		if(!EGinput.PressedKeys[SDLK_LSHIFT]){
			// normal jump
			EGplayer.move_speed=DEFAULT_MOVESPEED;
		} else {
			// sprint jump
			EGplayer.move_speed=DEFAULT_MOVESPEED*1.5; // some physics: gravity
		}
	}
	}

	// Mouse
	if(EGinput.mouse_left){
		// Destroy the block!
	} else if(EGinput.mouse_right){
		// Set a block
		EPlayEnvironmentSound(SND_SETBLOCK, 1);
	}


	// Send the new positions to the server
	if(EGinput.v_move_rel[0] != x)
		player_new_xpos(&EGinput.v_move_rel);
	if(EGinput.v_move_rel[2] != y)
			player_new_xpos(&EGinput.v_move_rel+2);
	if(EGinput.v_move_rel[1] != z)
			player_new_xpos(&EGinput.v_move_rel+1);
	

	pthread_mutex_unlock(&Tlock_input);
}
 
