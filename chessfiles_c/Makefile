#! /bin/sh

all: FENtranslator NEURAL_NET

FENtranslator: FENtranslator.o
	gcc FENtranslator.o -o FENtranslator

FENtranslator.o: FENtranslator.c
	gcc -c FENtranslator.c

NEURAL_NET: NEURAL_NET.o
	gcc NEURAL_NET.o -o NEURAL_NET

NEURAL_NET.o: NEURAL_NET.c
	gcc -c NEURAL_NET.c
	
clean:
	rm FENtranslator FENtranslator.o NEURAL_NET NEURAL_NET.o
