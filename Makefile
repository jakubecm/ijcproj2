# Makefile
# Řešení IJC-DU2, příklad 2), 13.4.2023
# Autor: Milan Jakubec, 1 BIT FIT
# Přeloženo: Apple clang verze 14.0.0


CC = gcc
CFLAGS = -g -O2 -std=c11 -pedantic -Wall -Wextra

HTAB_OBJS = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o htab_statistics.o

all: tail wordcount wordcount-dynamic

tail: tail.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fpic -c $<

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -static $^ -o $@

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) $^ -o $@

wordcount-cc: wordcount.cc
	g++ -std=c++17 -O2 -pedantic -Wall  $^ -o $@

libhtab.a: $(HTAB_OBJS)
	ar rcs $@ $^

libhtab.so: $(HTAB_OBJS)
	$(CC) $(CFLAGS) -fpic -shared $^ -o $@

run: tail wordcount wordcount-dynamic
	./tail <tail.c
	./wordcount <wordcount.c
	export LD_LIBRARY_PATH="." && ./wordcount-dynamic <wordcount.c

clean:
	rm -f *.o *.out *.zip tail wordcount wordcount-dynamic wordcountcpp libhtab.a libhtab.so wordcountcc

pack:
	zip xjakub41.zip *.c *.cc *.h Makefile