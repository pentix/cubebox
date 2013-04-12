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


#ifndef __CUBEBOX_SERVER_H__
#define __CUBEBOX_SERVER_H__

#define DEBUG

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "structs.h"
#include "config.h"
#include "net/net.h"

extern void _printf(char * _s_,...);

// All "global" functions
extern void Iconfig(void);
extern void Isockets(void);
extern void Iserver(void);
extern void Iexit(void);
extern void local_list_players(void);

#ifndef GLOB_VAR
	#define GLOB_VAR extern
#else
	void _printf(char * _s_,...){;}
#endif

#ifndef DEBUG
	#define printf(s, args...) _printf(s, ##args)
#endif

GLOB_VAR struct _config config;
GLOB_VAR unsigned short *(map_buffer[1]);

// Socket stuff
GLOB_VAR int tcp_socket;
GLOB_VAR struct sockaddr_in tcp_server_addr;

// Dynamic socket stuff
GLOB_VAR int thread_nr;
GLOB_VAR int thread_abs_nr;
GLOB_VAR pthread_t thread;
GLOB_VAR pthread_mutex_t lock_thread_nr;

// Players
struct _player *players;

#endif
