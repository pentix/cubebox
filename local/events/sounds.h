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


#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#define SOUNDSRC "res/sounds/%i.wav"
#define SOUNDSRCLEN 25

enum{
	SND_WALK=0,
	SND_RUN,
	SND_JUMP,
	SND_SETBLOCK,
	SOUNDS
};

#define MIX_PLAY_LOOP -1
#define MIX_PLAY_ONCE 0

#define AUDIO_RATE 22050				//Frequency of audio playback
#define AUDIO_FORMAT AUDIO_S16SYS		//Format of the audio we're playing
#define AUDIO_CHANNELS 2				//2 channels = stereo
#define AUDIO_BUFFERS 4096				//Size of the audio buffers in memory

#endif
