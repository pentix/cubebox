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
#include "net.h"
#include "server_commands.h"

/** \brief Create the socket needed and init it */
void Isockets(void){
	thread_nr=0;
	thread_abs_nr=0;
	
	// Request the socket
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(tcp_socket < 0){
		printf("Error on creating socket\n");
		exit(5);
	}
	
	// TCP Server settings
	tcp_server_addr.sin_family = AF_INET;
	tcp_server_addr.sin_port = htons(config.port);
	tcp_server_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind the sockets
	if(bind(tcp_socket, &tcp_server_addr, sizeof(tcp_server_addr))){
		printf("Error binding TCP socket!\n");
		exit(5);
	} else {
		printf("Socket sucessfully bound on port: %u\n", config.port); 
	}
}


/** \brief Main communication loop
 * 
 * This function gets called by the thread. The argument 
 * is a pointer to the socket to communicate with.
 *
 * See https://raw.github.com/wiki/0pq76r/cubebox/Multiplayer-Protocol-V1
 * for more information about the protocol.
 *
 * \param void* 	A pointer to the socket to communicate with 
 *
 */
void *talker( void *d ) {
	char logged_in=0;
	char buf[256];
	unsigned short playerid_buf;
	int fd;
	int i;

	fd = (int)d;

	pthread_mutex_lock(&lock_thread_nr);
		thread_nr++;
		
		if(config.max_players<thread_nr){
			pthread_mutex_unlock(&lock_thread_nr);
			printf("SERVER IS FULL!!\n");
			send(fd, (char *)ERR_SERVER_FULL, 1, 0);
			goto exit_talker;
		}
		
		thread_abs_nr++;
	pthread_mutex_unlock(&lock_thread_nr);
	
		// Find an empty player id!
		
		// NOTE: We can not increment the player id
		// because we use it as the index of the players
		// array!
		
		for(i=0; i<config.max_players; i++){
			if(strcmp((players+i)->username, "") == 0){
				break;
			}
		}
		playerid_buf=i;


	char username[21], password[21];
	
	if(!logged_in){
		if(!(recv(fd, buf, 1, 0)>0)){ // wait for the first Byte
			// No request, so quit!		
			goto exit_talker;
		}
		
		// If the first byte was login, create the user in the server...
		if(buf[0] == LOGIN){

			// Usernames are exactly 20 bytes long
			if(!(recv(fd, username, 20, 0)>0)) goto exit_talker;
			if(!(recv(fd, password, 20, 0)>0)) goto exit_talker;
			
			username[20]='\0';
			password[20]='\0';

			// (We will need it later)
			strcpy((players+playerid_buf)->username, username);
			(players+playerid_buf)->playerid = playerid_buf;
			
			// Server Output
			printf("User '%s' logged in with password '%s' using the player id %d\n", username, password, playerid_buf);
			printf("%d user(s) are connected to the server\n", thread_nr);
			
			send(fd, &playerid_buf, 2, 0);
		} else{ // Not logged in and no login command recv
			goto exit_talker;
		}
	}
	//login successfull

	while(recv(fd, buf, 1, 0)>0) {	// read command byte
		switch(buf[0]){
				default:
				case LOGOUT:
					// Remove the player out of the list of connected players
					strcpy((players+playerid_buf)->username, "");
					
					printf("User '%s' (player id %u) leaves\n", username, playerid_buf);				
					goto exit_talker;
				break;
				case '\r':break;
				case '\n':break;
		}
	}

exit_talker:
	pthread_mutex_lock(&lock_thread_nr);
		thread_nr--;
	pthread_mutex_unlock(&lock_thread_nr);
	printf("%d user(s) are connected to the server\n", thread_nr);
	
	close(fd);
	pthread_exit(NULL);
}


/** Start the socket infinite loops */
void Iserver(void){
	// Local socket buffers
	int connection_buffer;
	
	while(1){

		// Listen for player max+1 who tries to connect!
		listen(tcp_socket, config.max_players+1);
		connection_buffer = accept(tcp_socket, 0, 0);
		if(connection_buffer < 0){
			printf("Error accepting connection!\n");
			exit(5);
		}
		
		// Codesegment: Someone connected
		printf("Connection etablished!\n");
		
		pthread_create(&thread, NULL, talker, (void *)connection_buffer);
//		close(connection_buffer);
	}
}


/** Close the sockets */
void Iexit(void){
	if(close(tcp_socket) == 0)
		printf("Closed socket.\n");
}
