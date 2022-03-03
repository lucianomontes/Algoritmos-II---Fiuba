CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion

bf: pila.o bf.o

fixcol: fixcol.o

strutil: strutil.o
	

