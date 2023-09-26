#
# Compiles and executes the test program for the EDAT lab 3
PROGRAM_HOME=..

INSTALL_DIR=$(PROGRAM_HOME)/install
SOURCE_DIR=$(PROGRAM_HOME)/development/src
UTIL_DIR=
OTHER_DIR=

#
# These are some things about the compiler
#
CC=gcc -c 
LN=gcc

CFLAGS=-O -I/usr/include -I$(UTIL_DIR) -I$(SOURCE_DIR) -g

LFLAGS= -L/usr/lib/ -lm

OPTFILES=
INCLUDES= 
UTILFILES=
ALLFILES=cmds.o index.o import.o table.o type.o
LIBS=


all: test

#
# Files for the configuration file functions
#
cmds.o:	$(SOURCE_DIR)/cmds.c $(SOURCE_DIR)/cmds.h
	$(CC) $(CFLAGS) $(SOURCE_DIR)/cmds.c

index.o:	$(SOURCE_DIR)/index.c $(SOURCE_DIR)/index.h
	$(CC) $(CFLAGS) $(SOURCE_DIR)/index.c

import.o:	$(SOURCE_DIR)/import.c $(SOURCE_DIR)/import.h
	$(CC) $(CFLAGS) $(SOURCE_DIR)/import.c

table.o:	$(SOURCE_DIR)/table.c $(SOURCE_DIR)/table.h
	$(CC) $(CFLAGS) $(SOURCE_DIR)/table.c

type.o:	$(SOURCE_DIR)/type.c $(SOURCE_DIR)/type.h
	$(CC) $(CFLAGS) $(SOURCE_DIR)/type.c

main.o:	$(SOURCE_DIR)/main.c 
	$(CC) $(CFLAGS) $(SOURCE_DIR)/main.c



#
# Executable target
#
test:	main.o $(UTILFILES) $(ALLFILES)
	$(LN) $(LFLAGS) -o $(INSTALL_DIR)/test main.o $(UTILFILES) $(ALLFILES) $(LIBS)
