SRC_CLI = $(shell find ./local/ -name "*.c")
OBJ_CLI	= $(patsubst %.c,%.o, $(SRC_CLI))

SRC_SER = $(shell find ./server/ -name "*.c")
OBJ_SER	= $(patsubst %.c,%.o, $(SRC_SER))

TRG_CLI  = ./cubebox
TRG_SER  = ./cubebox-server

INSTALL_PATH=/usr/games/cubebox
BIN_DIR = /usr/bin/

CC = gcc
CP = cp
LN = ln
CHMOD = chmod
MKDIR = mkdir
CFLAGS  = $(shell sdl-config --libs --cflags) -lGL -lGLU -Wall -lSDL_mixer -lm -lpthread -lrt -g

all: client server

client: $(OBJ_CLI)
	$(CC) -o $(TRG_CLI) $(OBJ_CLI) $(CFLAGS) 

server: $(OBJ_SER)
	$(CC) -o $(TRG_SER) $(OBJ_SER) $(CFLAGS)

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS)

rebuild:
	superclean
	all
	
	
clean:
	rm -rf $(OBJ_CLI) $(OBJ_SER) startcubebox

superclean : clean
	rm -rf $(TRG_CLI) $(TRG_SER)
 
install: client server
	$(MKDIR) $(INSTALL_PATH) -p
	$(CP) $(TRG_CLI) res -r $(INSTALL_PATH)
	$(CP) $(TRG_SER) res -r $(INSTALL_PATH)
	sed 's|INSTALL_PATH|"${INSTALL_PATH}"|g' cubebox.sh > startcubebox
	$(CP) startcubebox $(BIN_DIR)/cubebox
	$(CHMOD) 755 $(BIN_DIR)/cubebox
	$(CHMOD) 755 $(INSTALL_PATH) -R
