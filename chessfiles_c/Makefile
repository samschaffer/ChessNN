#! /bin/sh

all: FENtranslator

FENtranslator: FENtranslator.o
	gcc FENtranslator.o -o FENtranslator

FENtranslator.o: FENtranslator.c
	gcc -c FENtranslator.c

clean:
	rm FENtranslator FENtranslator.o
