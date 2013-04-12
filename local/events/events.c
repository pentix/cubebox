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
 * MA 02110-1301, USAGLOB_VAR.
 * 
 */

#define EVENT_VAR
#define EG_VAR
#define ES_VAR
#include "events.h"
#include "../event_graphic_port.h"
#include "../event_net_port.h"


/** \brief Init memory for a player structure
 *	\param _player	A pointer to the player structure to be initialized
*/
void Einit_player(){
	pthread_mutex_lock(&Tlock_input);
	EGplayer.look[0]     = 0;
	EGplayer.look[1]     = 0;
	EGplayer.pos_abs[0]  = 0;
	EGplayer.pos_abs[1]  = 5;
	EGplayer.pos_abs[2]  = 0;
	EGplayer.move_speed  = 0; 
	EGplayer.jump        = 0;
	pthread_mutex_unlock(&Tlock_input);
}

void* Tevent_loop(void *x){
	struct timespec Lstart, Lfinish;
	double Lelapsed;
	
	Einit_player();
	Eload_sounds();
	pthread_mutex_lock(&Tlock_cubes);
	pthread_mutex_unlock(&Tlock_cubes);

	while(!EGSgame_exit){
		clock_gettime(CLOCK_MONOTONIC, &Lstart);

		Einput();
		Emove_player();
		Egravity();
		//~ Ecollision();

		clock_gettime(CLOCK_MONOTONIC, &Lfinish);
		Lelapsed = (Lfinish.tv_sec - Lstart.tv_sec)*1000000;
		Lelapsed += (Lfinish.tv_nsec - Lstart.tv_nsec) / 1000.0;
		if(((1000000.0f/(float)EventClock)-Lelapsed)>0){
			usleep((1000000.0f/(float)EventClock)-Lelapsed);
		} else {
			printf("Your event thread is %f usec too slow\n",((1000000.0f/(float)EventClock)-Lelapsed));
		}
	}
	pthread_exit(NULL);
}
