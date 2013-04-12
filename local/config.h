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


#ifndef __CONFIG_H__
#define __CONFIG_H__

// 64 space characters
#define SPACE_PAD "                                                                "

/** \brief Client settings */
struct _config{
	int screen_height;
	int screen_width;
	int screen_bpp;
	int screen_fps_limit;
	float mouse_sensitivity;
	char  server_ip[17];
	int  server_port;
	char  user_name[21];
	char  password[21];
	char  texturepack[64];
};

#endif
