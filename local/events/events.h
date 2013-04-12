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


#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "sounds.h"
#include "../cubebox.h"

#ifndef EVENT_VAR
	#define EVENT_VAR extern
#endif

#define EventClock 50

extern void Einput(void);
extern void Eload_sounds(void);
extern void Ecollision(void);
extern void Emove_player(void);
extern void Egravity(void);
extern void EPlayEnvironmentSound(int Lsound_type, char Lforce);

EVENT_VAR Mix_Music *Esound[SOUNDS];
EVENT_VAR char Esound_active;
EVENT_VAR SDL_Event e;

#endif
