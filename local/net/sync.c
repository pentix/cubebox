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


#include "../cubebox.h"
#include "net.h"

unsigned short *Sget_cube(long x, long y, long z){
	short f;
	unsigned short *S=(unsigned short*)malloc(2*16*16*16);
	
	for(f=0;f<16*16*16;f++){
		if((f%7!=0)&&((f/16)%16!=15)&&((f/16)%16!=14)){
			S[f]=1;
		}
	}
	return S;
}
