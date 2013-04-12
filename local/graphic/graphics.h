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


#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "../cubebox.h"

#define SDL_FLAGS SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWSURFACE | SDL_NOFRAME// | SDL_FULLSCREEN

#ifndef GRAPH_VAR
	#define GRAPH_VAR extern
#endif

#define BLOCKTEXTURESRCLEN 128
char blocktexturesrc[BLOCKTEXTURESRCLEN];


#ifndef BLOCKTEXTURESNUM
	#define BLOCKTEXTURESNUM 2
#endif
#ifndef BLOCKSUBTEXTURES				//Subtexture while destroying
	#define BLOCKSUBTEXTURES 1
#endif
#define BLOCKSIDES 1 					//BLOCKSIDES 2 => block with diffrent top texture
#define BLOCKTEXTURESNAME "%iblock%itex%i.bmp"
#define BLOCKTEXTURESNAMELEN 20

GRAPH_VAR GLuint BlockTextures[BLOCKTEXTURESNUM][BLOCKSIDES][BLOCKSUBTEXTURES];
GRAPH_VAR GLuint Gprerenderedcubes[CUBES_IN_RAM];
GRAPH_VAR GLuint Gground;


extern void Gblock_display_list();
extern void Gcube_grid(void);
extern void Ginit_ground(void);
extern void Gdraw_ground(void);
extern void Gmove_camera();
extern void Gdraw_block(float x, float y, float z, int texture);
extern void Gdisplay_objects(void);

#endif
