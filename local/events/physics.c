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

void Ecollision(void){
	pthread_mutex_lock(&Tlock_input);
	pthread_mutex_lock(&Tlock_cubes);

	float cubex=(((EGplayer.pos_abs[0]-EGplayer.move_speed*EGinput.v_move_rel[0]))/16.0f);
	float cubey=((((EGplayer.pos_abs[1]-DEFAULT_MOVESPEED*EGinput.v_move_rel[1]))+1)/16.0f);
	float cubez=((((EGplayer.pos_abs[2]-EGplayer.move_speed*EGinput.v_move_rel[2])))/16.0f);
	
	int x=(int)floor((cubex*16.0f))%16;
	int y=(int)floor((cubey*16.0f))%16;
	int z=(int)floor((cubez*16.0f))%16;
	
	
	while(x<0){x+=16;cubex-=1;}
	while(y<0){y+=16;cubey-=1;}
	while(z<0){z+=16;cubez-=1;}
	
	if(EGinput.v_move_rel[0]<0){
		x=(int)floor((cubex*16.0f)+0.2f)%16;
	} else {
		x=(int)floor((cubex*16.0f)-0.2f)%16;
	}
	
	if(EGinput.v_move_rel[2]<0){
		z=(int)floor((cubez*16.0f)+0.2f)%16;
	} else {
		z=(int)floor((cubez*16.0f)-0.2f)%16;
	}

	if((int)cubex+(int)cubey+(int)cubez==0){

	//block below
		if((EGScubes[0][((int)x)+((int)(y)*16)+((int)z*256)])!=0){
			if(EGinput.v_move_rel[1]>0){
				EGinput.v_move_rel[1]=0;
				EGplayer.jump=0;
			}
			if(EGplayer.pos_abs[1]-(int)EGplayer.pos_abs[1]>=0.05){
				EGplayer.jump=2;
			}
		}

		if((EGScubes[0][((int)x)+((int)(y+1)*16)+((int)z*256)])!=0){
				EGinput.v_move_rel[0]=0;
				EGinput.v_move_rel[2]=0;
		}

		if((EGScubes[0][((int)x)+((int)(y+2)*16)+((int)z*256)])!=0){
			EGinput.PressedKeys[SDLK_LCTRL]+=2;
		} else if((EGinput.PressedKeys[SDLK_LCTRL]&1)==0){
			EGinput.PressedKeys[SDLK_LCTRL]=0;
		}
	}
	pthread_mutex_unlock(&Tlock_input);
	pthread_mutex_unlock(&Tlock_cubes);
}


void Egravity(void){
	pthread_mutex_lock(&Tlock_input);
	EGinput.v_move_rel[1]+=2;
	pthread_mutex_unlock(&Tlock_input);
}
