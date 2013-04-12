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


#ifndef __NET_H__
#define __NET_H__

#include "../cubebox.h"
#include "server_commands.h"

extern unsigned short* Sget_cube(long x, long y, long z);
extern int Isockets(short* id);
extern void Stalker(int socket);

int tcp_socket;
struct sockaddr_in tcp_server_addr;

int udp_socket;
struct sockaddr_in udp_server_addr;

char server_motd[64];

#endif
