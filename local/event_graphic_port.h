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


#ifndef __EVENT_GRAPHIC_PORT_H__
#define __EVENT_GRAPHIC_PORT_H__

#define DEFAULT_MOVESPEED 0.05f
#define PLAYER_HEIGHT 1.75f

#ifndef EG_VAR
	#define EG_VAR extern
#endif

EG_VAR struct _player EGplayer;
EG_VAR struct _input EGinput;
EG_VAR char EGday;

#endif
