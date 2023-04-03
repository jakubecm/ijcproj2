# Makefile for compilation of tail.c 
# 


CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra


CFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address

all: tail

clean:
	rm -f tail tail.o
