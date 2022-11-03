matriz.o:  matriz.h matriz.c
	gcc -Wall -g -c matriz.c -o matriz.o

proy1: proy1.c matriz.o
	gcc -Wall -g -o proy1 proy1.c matriz.o

