# Makefile for compilation
# Autor: Milan Jakubec
# Login: xjakub41

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall

TARGETS= tail libhtab.a libhtab.so wordcount wordcount-dynamic
LIB_OBJECTS=htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o htab_statistics.o
WORDCOUNT_OBJECTS=libhtab.a io.o worcount.o
WORDCOUNT_DYNAMIC_OBJECTS=libhtab.so io.o worcount.o


all: $(TARGETS)

tail: tail.o
	$(CC) $(CFLAGS) -o tail tail.o

%.o: %.c htab.h hash_tab_struct.h
	$(CC) $(CFLAGS) -fpic -c $<

wordcount-: wordcount-.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

wordcount: $(WORDCOUNT_OBJECTS)
	$(CC) $(CFLAGS) -static $^ -o $@

wordcount-dynamic: $(WORDCOUNT_DYNAMIC_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

libhtab.a: $(LIB_OBJS)
	ar rcs $@ $^

libhtab.so: $(LIB_OBJS)
	$(CC) -fpic -shared $^ -o $@

clean:
	rm *.o $(TARGETS)

pack:
	zip xjakub41.zip *.c *.h *.cc Makefile