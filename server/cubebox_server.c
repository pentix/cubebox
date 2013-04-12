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
#include "cubebox_server.h"

/** \brief Wait for inputs on the server side and execute the commands */
void *Uinput(){
	char inputbuffer[64];
	
	while(1){
		fgets(inputbuffer, 64, stdin);
		inputbuffer[strlen(inputbuffer)-1] = '\0';
		
		// Exit on 'q'
		if(strcasecmp(inputbuffer, "q") == 0)
			exit(0);
		
		else if(strcasecmp(inputbuffer, "list") == 0)
			local_list_players();
	}
}


/** \brief Allocate memory for structures we need later */
void Iinit_memory(void){
	players = (struct _player *)calloc(1, sizeof(struct _player)*config.max_players);
	if(players == NULL){
		printf("Could not allocate memory for all players!\n");
		exit(1);
	}
}


/** \brief Free all used memory */
void Ifree_memory(void){
	free(players);
}


int main(int argc, char *argv[]){
	pthread_t input_thread;

	pthread_mutex_init(&lock_thread_nr,NULL);
	pthread_create(&input_thread, NULL, Uinput, NULL);
	Iconfig();
	Iinit_memory();
	
	Isockets();
	Iserver();
	
	// @ exit functions
	atexit(Iexit);
	atexit(Ifree_memory);
	return 0;
}
