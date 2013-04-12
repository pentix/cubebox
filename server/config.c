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


#include "cubebox_server.h"

/** \brief Local key-value-pair struct */
struct key_value{
	char *key;
	char *value;
};


/** \brief Split one line 
 * 
 * \return char*	A pointer to the line read
 * \param FILE 		A stream to read bytes from
*/
char *next_line(FILE *stream){
	unsigned int buffersize=32, i=0;
	char *line = (char*)malloc(buffersize);
	char byte='\0';
	
	// Init the line
	strcpy(line, "\0");
	
	while(byte != '\n'){
		fread(&byte, 1, 1, stream);
		strncat(line, &byte, 1);	// We only want 1 byte
		
		if(feof(stream))
			return line;
		
		// Auto realloc
		if(++i == buffersize-1){	// -  '\0'
			buffersize*=2;			// take a 2^n value
			line = (char *)realloc(line, buffersize);
			if(line == NULL){
				printf("Error allocating memory\n");
				exit(1);
			}
		}
	}
	
	// Cut the newline character at the end
	*(line+strlen(line)-1) = '\0';
	
	return line;
}

/** \brief	Parse a string into a key/value pair
 *  
 * We use the tab character as the seperator between keys and values.
 * Additionally, we ignore tab characters inside the values.
 * 
 *  \return key_value*	A pointer to the key/value pair
 *  \param  char*		A pointer to the line to be parsed
*/
struct key_value *get_pair(char *line){
	static struct key_value *pair;
	static char init=0;
	
	if(init == 0){
		pair = (struct key_value *)malloc(sizeof(struct key_value));
		init = 1;
	}
	
	unsigned int buffersize=16, i=0;
	
	// Allocate and init the memory for the key
	pair->key = (char *)malloc(buffersize);
	strcpy(pair->key, "");
	
	// Read the key
	while(*(line+i) != '\t' && strcmp(line, "") != 0){
		// Check for comments
		if(*(line+i) == '#'){
			break;
		}
		
		strncat(pair->key, (line+i), 1);		// We only want 1 byte
		
		if(++i == buffersize-1){				// -  '\0'
			buffersize *= 2;					// take a 2^n value
			pair->key = (char *)realloc(pair->key, buffersize);
			if(pair->key == NULL){
				printf("Error allocating memory\n");
				exit(1);
			}
		}
	}
	
	// Reset dynamic memory allocation variables
	buffersize = 16;
	unsigned int k=0;	// New one for counting the size since *list[i]
	
	// Allocate and init the memory for the value
	pair->value = (char *)malloc(buffersize);
	strcpy(pair->value, "\0");
	
	// Now read the rest into the value!
	while(*(line+i) != '\0'){
		if(*(line+i) != '\t'){	// ignore tabs
			strncat(pair->value, (line+i), 1);	// We only want 1 byte
		}
		
		++i;
		
		// Auto realloc
		if(++k == buffersize-1){				// -  '\0'
			buffersize *= 2;					// take a 2^n value
			pair->value = (char *)realloc(pair->value, buffersize);
			if(pair->value == NULL){
				printf("Error allocating memory\n");
				exit(1);				
			}
		}	
	}
	
	
	return pair;
}


/** \brief Parse the config file into the default _config struct */
void Iconfig(void){
	FILE* Lconf;
	Lconf=fopen("res/config/server.conf","r");
	
	struct key_value *Lpair;
	char *Lline;
	
	if(Lconf != NULL){
		
		do{
			Lline = next_line(Lconf);
			Lpair = get_pair(Lline);

			if(strcasecmp(Lpair->key, "name") == 0){		// We don't care about case sensitivity!
				strncpy(config.name, Lpair->value, 64);
			} else if(strcasecmp(Lpair->key, "motd") == 0){
				strncpy(config.motd, Lpair->value, 256);
			} else if(strcasecmp(Lpair->key, "port") == 0){
				if(atoi(Lpair->value) > 65534 || atoi(Lpair->value) < 1025){
					printf("Error: Port must be a number between 1025 and 65534\n");
					exit(5);
				} else {
					config.port = (unsigned short)atoi(Lpair->value);
				}
			} else if(strcasecmp(Lpair->key, "map_path") == 0){
				strncpy(config.map_path, Lpair->value, 64);
			} else if(strcasecmp(Lpair->key, "max_players") == 0){
				config.max_players = (unsigned short)atoi(Lpair->value);
			}
			
			// We don't need the pair anymore
			free(Lpair->key);
			free(Lpair->value);
			
		} while(!feof(Lconf));
		
		
		printf("Loaded name: '%s'\n", config.name);
		printf("Loaded motd: '%s'\n", config.motd);
		printf("Loaded port:  %d\n", config.port);
		printf("Loaded map_path: '%s'\n", config.map_path);
		printf("Loaded max_players: %u\n", config.max_players);
		
		fclose(Lconf);
	} else {
		printf("Error: Could not read config file\n");
		exit(4);
	}
	
	
}
