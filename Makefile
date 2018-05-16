#! /bin/sh

all: FENtranslator NEURAL_NET MASTER_AI

FENtranslator: FENtranslator.o
	gcc FENtranslator.o -o FENtranslator

NEURAL_NET: NEURAL_NET.o
	gcc NEURAL_NET.o -o NEURAL_NET

MASTER_AI: MASTER_AI.o
	gcc MASTER_AI.o -o MASTER_AI
	
FENtranslator.o: FENtranslator.c
	gcc -c FENtranslator.c

NEURAL_NET.o: NEURAL_NET.c
	gcc -c NEURAL_NET.c

MASTER_AI.o: MASTER_AI.c
	gcc -c MASTER_AI.c
	
clean:
	rm FENtranslator FENtranslator.o NEURAL_NET NEURAL_NET.o MASTER_AI MASTER_AI.o
