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

#ifndef __SERVER_COMMANDS_H__
#define __SERVER_COMMANDS_H__

#define LOGIN 			0x47
#define LOGIN_ERROR		0x41
#define LOGIN_OK		0x22

#define GET_MAP			0x33
#define GET_MAP_ERROR 	0x40
#define GET_MAP_OK		0x43

#define SET_BLOCK		0x26
#define SET_BLOCK_ERROR 0x49
#define SET_BLOCK_OK	0x21

#define RM_BLOCK		0x25
#define RM_BLOCK_ERROR	0x45
#define RM_BLOCK_OK		0x24

#define NEW_X_POSITION	0x50
#define NEW_Y_POSITION	0x51
#define NEW_Z_POSITION	0x52

#define LOGOUT			0X46

#endif
