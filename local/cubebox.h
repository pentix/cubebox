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


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_opengl.h>
#include <SDL/SDL_mixer.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>


#ifndef __CUBEBOX_H__
#define __CUBEBOX_H__

#ifndef GLOB_VAR
	#define GLOB_VAR extern
#else
	void _printf(char * _s_,...){;}
#endif

#include "config.h"
#include "structs.h"

#define SyncRate 3

extern void _printf(char * _s_,...);

// As long as we are in a development phase
#define DEBUG

#ifndef DEBUG
	#define printf(s, args...) _printf(s, ##args)0
#endif

#define MIN_CUBES_IN_RAM (10*10*10)
#define OPTIONAL_CUBES_IN_RAM 100
#define CUBES_IN_RAM MIN_CUBES_IN_RAM+OPTIONAL_CUBES_IN_RAM

GLOB_VAR struct _config config;
GLOB_VAR char EGSgame_exit;
GLOB_VAR unsigned short *EGScubes[CUBES_IN_RAM];
GLOB_VAR int EGScube_list[CUBES_IN_RAM][3];

GLOB_VAR pthread_t Tevent;
GLOB_VAR pthread_t Tmap_sync;
GLOB_VAR pthread_mutex_t Tlock_input;
GLOB_VAR pthread_mutex_t Tlock_cubes;
GLOB_VAR pthread_mutex_t Tsync_cubes;


// All "global" functions
extern void Iconfig(void);
extern void Iinit_screen(void);
extern void Iinit_player();
extern void Iinit_config(struct _config *config);
extern void Iload_sounds(void);
extern void Iload_block_textures(void);

extern void Tgraphic_loop();
extern void *Tsync_loop(void *x);
extern void *Tevent_loop(void *x);

extern void quit(void);

#endif
