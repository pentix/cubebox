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


#include "../cubebox_server.h"

/** \brief List all players connected. (server side only) */
void local_list_players(void){
	int i;
	unsigned short connected_players=0;
	
	printf("Connected players:\n");
	
	for(i=0; i<config.max_players; i++){
		if(strcmp((players+i)->username, "") != 0){
			printf("%s ", (players+i)->username);
			connected_players++;
		}
	}
	
	printf("\n%u out of max. %u players connected\n", connected_players, config.max_players);
}
