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


#include "../cubebox.h"
#include "net.h"


void Stalker(int socket){
	
}

/** \brief Init the sockets */
int Isockets(short* id){
	int tcp_socket;
	struct sockaddr_in tcp_server_addr;
	
	int udp_socket;
	struct sockaddr_in udp_server_addr;
	
	// Request the socket
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(tcp_socket < 0 || udp_socket < 0){
		printf("Error on creating sockets\n");
		exit(5);
	}
	
	// TCP Server settings
	tcp_server_addr.sin_family = AF_INET;
	tcp_server_addr.sin_port = htons(config.server_port);
	tcp_server_addr.sin_addr.s_addr = inet_addr(config.server_ip);

	// UDP Server settings
	udp_server_addr.sin_family = AF_INET;
	udp_server_addr.sin_port = htons(config.server_port+1);				// UDP Port is one above the TCP port
	udp_server_addr.sin_addr.s_addr = inet_addr(config.server_ip);


	// Bind the sockets
	if(connect(tcp_socket, &tcp_server_addr, sizeof(tcp_server_addr))){
		printf("Failed to connect using the TCP socket!\n");
		exit(5);
	}

	if(connect(udp_socket, &udp_server_addr, sizeof(udp_server_addr))){
		printf("Failed to connect using the TCP socket!\n");
		exit(5);
	}

	
	// Login using the tcp socket
	char login[42]={0};
	login[0]=LOGIN;
	
	// Copy maximum 20 bytes
	strncat(login, config.user_name,20);
	strncat(login, config.password, 20);
	
	send(tcp_socket, login, 41, 0);
	recv(tcp_socket, id, 2, 0);
	recv(tcp_socket, server_motd, 64, 0);

	printf("\n=== %s ===\n", server_motd);
	
	
	return tcp_socket;
}


/** \brief Send the new x position of the player to the server */
void player_new_xpos(float *x){
	char player_position[6] = {0};
	player_position[0] = NEW_X_POSITION;
	memcpy(&player_position+1, x, sizeof(float));
	
	sendto(udp_socket, player_position, 5, 0, (struct sockaddr *)&udp_server_addr, sizeof(udp_server_addr));
}


/** \brief Send the new y position of the player to the server */
void player_new_ypos(float *y){
	char player_position[6] = {0};
	player_position[0] = NEW_Y_POSITION;
	memcpy(&player_position+1, y, sizeof(float));
	
	sendto(udp_socket, player_position, 5, 0, (struct sockaddr *)&udp_server_addr, sizeof(udp_server_addr));
}


/** \brief Send the new z position of the player to the server */
void player_new_zpos(float *z){
	char player_position[6] = {0};
	player_position[0] = NEW_Z_POSITION;
	memcpy(&player_position+1, z, sizeof(float));
	
	sendto(udp_socket, player_position, 5, 0, (struct sockaddr *)&udp_server_addr, sizeof(udp_server_addr));
}

