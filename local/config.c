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


#include "cubebox.h"

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
char *Lnext_line(FILE *stream){
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
struct key_value *Lget_pair(char *line){
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
	Lconf=fopen("res/config/client.conf","r");
	
	struct key_value *Lpair;
	char *Lline;
	
	if(Lconf != NULL){
		
		do{
			Lline = Lnext_line(Lconf);
			Lpair = Lget_pair(Lline);
			
			if(strcasecmp(Lpair->key, "screen_width") == 0)		// We don't care about case sensitivity!
				config.screen_width = atoi(Lpair->value);
			else if(strcasecmp(Lpair->key, "screen_height") == 0)
				config.screen_height = atoi(Lpair->value);
			else if(strcasecmp(Lpair->key, "screen_bpp") == 0)
				config.screen_bpp = atoi(Lpair->value);
			else if(strcasecmp(Lpair->key, "screen_fps_limit") == 0)
				config.screen_fps_limit = atoi(Lpair->value);
			else if(strcasecmp(Lpair->key, "mouse_sensitivity") == 0)
				config.mouse_sensitivity = atof(Lpair->value);
			else if(strcasecmp(Lpair->key, "server_ip") == 0)
				strncpy(config.server_ip, Lpair->value, 17);
			else if(strcasecmp(Lpair->key, "server_port") == 0)
				config.server_port = atoi(Lpair->value);
			else if(strcasecmp(Lpair->key, "user_name") == 0)
				strncpy(config.user_name, Lpair->value, 20);
			else if(strcasecmp(Lpair->key, "password") == 0)
				strncpy(config.password, Lpair->value, 20);
			else if(strcasecmp(Lpair->key, "texturepack") == 0)
				strncpy(config.texturepack, Lpair->value, 64);
		
			// We don't need the pair anymore
			free(Lpair->key);
			free(Lpair->value);
			
		} while(!feof(Lconf));
		
		
		printf("Loaded screen_width: %d\n", config.screen_width);
		printf("Loaded screen_height: %d\n", config.screen_height);
		printf("Loaded screen_bpp: %d\n", config.screen_bpp);
		printf("Loaded screen_fps_limit: %d\n", config.screen_fps_limit);
		printf("Loaded mouse_sensitivity: %f\n", config.mouse_sensitivity);		
		printf("Loaded server_ip: '%s'\n", config.server_ip);
		printf("Loaded server_port: %d\n", config.server_port);
		printf("Loaded password: '%s'\n", config.password);	
		printf("Loaded user_name: '%s'\n", config.user_name);
		printf("Loaded texturepack: '%s'\n", config.texturepack);
		
		strncat(config.user_name, SPACE_PAD, 20-strlen(config.user_name));
		config.user_name[20]='\0';
		strncat(config.password, SPACE_PAD, 20-strlen(config.password));
		config.password[20]='\0';
		
		fclose(Lconf);
	} else {
		printf("Error: Could not read config file\n");
		exit(4);
	}
	
	
}
