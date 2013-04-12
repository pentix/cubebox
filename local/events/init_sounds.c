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


#include "events.h"

/** \brief Load the sound to the sound array */
void Eload_sounds(void){
	int i;
	char soundsrc[SOUNDSRCLEN]=SOUNDSRC;
	char *buf=SOUNDSRC;

	Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS);

	for(i=0;i<SOUNDS;i++){
		sprintf(soundsrc, buf, i);
		Esound[i] = Mix_LoadMUS(soundsrc);
		if(Esound[i]<0){
			printf("Failed to load: '%s'\n", soundsrc);
			exit(3);
		} else{
			printf("Loaded: '%s'\n", soundsrc);	
		}
	}
}
