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

/** \brief Gets called when there was an input event
 * 
 * The whole control is here!
*/
void Einput(void){
	pthread_mutex_lock(&Tlock_input);
	
	EGplayer.height=PLAYER_HEIGHT;

	while(SDL_PollEvent(&e)==1){
		if(e.type==SDL_QUIT){
			EGSgame_exit=1;
		}
		if(e.type==SDL_KEYDOWN){;
			EGinput.PressedKeys[e.key.keysym.sym]=1;
			if(EGinput.PressedKeys[SDLK_SPACE] && EGplayer.jump <=0 && !EGinput.PressedKeys[SDLK_LCTRL])
				EGplayer.jump=20;
		}
		if(e.type==SDL_KEYUP){;
			EGinput.PressedKeys[e.key.keysym.sym]=0;
		}
		if(e.type==SDL_MOUSEBUTTONDOWN){
			if(e.button.button==SDL_BUTTON_LEFT) EGinput.mouse_left=1;
			if(e.button.button==SDL_BUTTON_RIGHT) EGinput.mouse_right=1;
		}
		if(e.type==SDL_MOUSEBUTTONUP){
			if(e.button.button==SDL_BUTTON_LEFT) EGinput.mouse_left=0;
			if(e.button.button==SDL_BUTTON_RIGHT) EGinput.mouse_right=0;
		}
		if(e.type==SDL_MOUSEMOTION){
			EGinput.mouse_move_xrel=e.motion.xrel;
			EGinput.mouse_move_yrel=e.motion.yrel;
			EGplayer.look[0]+=EGinput.mouse_move_yrel*config.mouse_sensitivity;
			EGplayer.look[1]+=EGinput.mouse_move_xrel*config.mouse_sensitivity;
			if(EGplayer.look[1]>360)EGplayer.look[1]-=360;
			if(EGplayer.look[1]<0)EGplayer.look[1]+=360;
		}
	}
	
	// Exit the game
	if(EGinput.PressedKeys[SDLK_ESCAPE])
		EGSgame_exit=1;

	//Day
	if(EGinput.PressedKeys[SDLK_l])
		EGday=0;

	//Night
	if(EGinput.PressedKeys[SDLK_n])
		EGday=1;

	//Night with torch
	if(EGinput.PressedKeys[SDLK_f])
		EGday=2;
	pthread_mutex_unlock(&Tlock_input);
}
 
