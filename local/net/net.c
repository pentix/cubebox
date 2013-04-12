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

#define NET_VAR

#include "../cubebox.h"
#include "net.h"

/** \brief The game loop that is responsible for everything.
 * 
 *  This function is called inside an infinite loop.
*/
void *Tsync_loop(void *x){
	struct timespec Lstart, Lfinish;
	double Lelapsed;
	short player_id;
	int socket;
	
	pthread_mutex_lock(&Tsync_cubes);
	pthread_mutex_lock(&Tlock_cubes);
	pthread_mutex_unlock(&Tlock_cubes);
	
	socket=Isockets(&player_id);

	if(player_id<=0){
		printf("Login failed.\n");
		exit(5);
	}

	printf("Got id %i\n", player_id);
	
	while(!EGSgame_exit){
		clock_gettime(CLOCK_MONOTONIC, &Lstart);

		Stalker(socket);

		clock_gettime(CLOCK_MONOTONIC, &Lfinish);
		Lelapsed = (Lfinish.tv_sec - Lstart.tv_sec)*1000000;
		Lelapsed += (Lfinish.tv_nsec - Lstart.tv_nsec) / 1000.0;
		if(((1000000.0f/(float)SyncRate)-Lelapsed)>0){
			usleep((1000000.0f/(float)SyncRate)-Lelapsed);
		} else {
			printf("Your sync thread is %f usec too slow\n",((1000000.0f/(float)config.screen_fps_limit)-Lelapsed));
		}
	}
	pthread_mutex_unlock(&Tsync_cubes);
	close(socket);
	pthread_exit(NULL);
}
