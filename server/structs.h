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


#ifndef __STRUCT_H__
#define __STRUCT_H__

/** \brief Everything relating to the player (including connection details) */
struct _player{
	float look[2];
	float pos_abs[3];
	float move_speed;
	float height;
	unsigned char jump;
	
	// Protocol stuff
	unsigned short playerid;
	char username[20];
};

#endif
