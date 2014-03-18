# Makefile for predprey.exe
# Author : Suharh Sivakumar
# Date of creation : January 27, 2012

CFLAGS = -c -g -Wall
LFLAGS = -framework OpenGL -framework GLUT -framework Cocoa

BINARIES = predprey

all : $(BINARIES)

clean : 
	DEL *.o $(BINARIES)
	
predprey : eco.o predprey.o
	g++ eco.o predprey.o $(LFLAGS) -o predprey

predprey.o : predprey.cpp eco.h
	g++ $(CFLAGS) predprey.cpp
	
eco.o : eco.cpp eco.h
	g++ $(CFLAGS) eco.cpp