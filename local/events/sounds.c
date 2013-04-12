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


/** \brief Gets called when a sound is finished (Callback function)
 * 
 * The sound_active variable is set to 0, which
 * allows to play the next sound. This would
 * also be possible if you force it.
*/
void LSoundPlayed(void){
	Mix_PauseMusic();
	Esound_active=0;
}

/** \brief Play a sound
 * 	\param int 		The number of the sound to be played
 *  \param char		If this is 1, the sound will be played, even if there is another sound in the buffer
*/
void EPlayEnvironmentSound(int Lsound_number, char Lforce){
	if((!Esound_active)||(Lforce)){
		Mix_PlayMusic(Esound[Lsound_number], MIX_PLAY_ONCE);
		Esound_active=1;
		Mix_HookMusicFinished(LSoundPlayed);
	}
}
