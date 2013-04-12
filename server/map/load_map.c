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


#include "../cubebox_server.h"

//return next free map buffer
long nfreembuf(){
	return 0;
}

//return index of new allocated map buffer
long nmbuf(){
	map_buffer[0]=(unsigned short*)malloc(16*16*16*2);
	return 0;
}

unsigned short *generate_cube(x,y,z){
	unsigned short *map;
	int i;
	map=(unsigned short*)malloc(16*16*16*2);
	for(i=0;i<16*16*16;i++){
		map[i]=(i%3);
	}
	return map;
}

short map_in_buffer(){
	return -1;
}
	char tcp_socket_buffer[128];

//x y z = player x y z /16
unsigned short *get_cube(long x, long y, long z){
	unsigned short *cube;
	short i;
	#ifdef DEBUG
		char map_path[] = "res/map/0/";
	#endif
	//Check if in buffer
	if((i=map_in_buffer())>=0){
		cube=map_buffer[i];
		return cube;
	}


	FILE* chunk;
	char *chunkfile, *buf;
	unsigned char cubes[32]={0};

	chunkfile=(char*)malloc(strlen(map_path)+30);
	buf=(char*)malloc(strlen(map_path)+30);
	strcpy(buf, map_path);
	strcat(buf, "/%i_%i.cbm");
	sprintf(chunkfile, buf, x, y);

	//Create file if not exist
	chunk=fopen(chunkfile, "a+b");
	fclose(chunk);

	//Open in read+edit mode
	chunk=fopen(chunkfile, "r+b");
		free(buf);
		free(chunkfile);
		rewind(chunk);

		//read index
		fread(cubes, 1, 32, chunk);
		if(cubes[z]==0){
			cube=map_buffer[nfreembuf()]=generate_cube(x,y,z);

			int s;
			fseek(chunk, 0, SEEK_END);
			cubes[z]=s=(ftell(chunk)>>13)+1;

			rewind(chunk);
			fwrite(cubes, 1, 32, chunk);

			fseek(chunk, 0, SEEK_END);
			fwrite(cube, 2, 16*16*16, chunk);
		} else {
			int i=nmbuf();
			rewind(chunk);
			fseek(chunk, 32+(16*16*16*2*(cubes[z]-1)), SEEK_SET);
			fread(map_buffer[i], 2, 16*16*16, chunk);
			cube=map_buffer[i];
		}
	fclose(chunk);
	return cube;
}
