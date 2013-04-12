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


#define GLOB_VAR 
#include "cubebox.h"

/** \brief main() 
 * 
 * 	This functions initializes evrything and starts the main loop
*/
int main(int argc, char *argv[]){
	pthread_mutex_init(&Tlock_input, NULL);
	pthread_mutex_init(&Tlock_cubes, NULL);
	pthread_mutex_init(&Tsync_cubes, NULL);

	pthread_mutex_lock(&Tlock_cubes);

	pthread_create(&Tevent, NULL, Tevent_loop, NULL);
	pthread_create(&Tmap_sync, NULL, Tsync_loop, NULL);

	Iinit_config(&config);
	Iconfig();
	Iinit_screen();
	Iload_block_textures();
	
	pthread_mutex_unlock(&Tlock_cubes);	

	Tgraphic_loop();
	pthread_join(Tevent, NULL);
	pthread_join(Tmap_sync, NULL);

	printf("\n");
	return 0;
}
