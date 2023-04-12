


#include "htab.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
/*
Tohle cislo jsem si vybral na zaklade toho, ze prumerna kniha ma podle googlu do 10 000 UNIKATNICH slov.
Studoval jsem trochu jak funguje ta hash tabulka a zjistil jsem ze je doporucene pouzit prvocislo pro lepsi
efektivitu, a proto jsem se rozhodl pro 10 007.
*/
#define HTAB_SIZE 10007 
#define MAX_WORD_LEN 255 // 255 + '\0'


#ifdef HASHTEST
// http://www.cse.yorku.ca/~oz/hash.html - varianta lose lose):
size_t htab_hash_function(const char* str) {
	unsigned int hash = 0;
	int c;

	while (c = *str++)
	    hash += c;

	return hash;
}
#endif

void print_pairs(htab_pair_t *pair) {
  printf("%s\t%d\n", pair->key, pair->value);
}

int main(void) {
    
    htab_t* t = htab_init(HTAB_SIZE); // Inicializuje tabulku
    
    if (!t) {
        fprintf(stderr, "Error: Problem with allocating memory for hashtable. Exiting...\n");
        return EXIT_FAILURE;
    }

    // Nacitani slov ze stdin
    int length = 0;

    while (length != EOF) {
        char key[MAX_WORD_LEN] = {0};
        length = read_word(key, MAX_WORD_LEN, stdin);

        if (length == EOF) {
            break;
        }

        htab_pair_t* pair = htab_lookup_add(t, key);
        if (pair == NULL) {
            fprintf(stderr, "Eror: Couldnt insert pair into table. Exiting...\n");
            htab_free(t);
            return EXIT_FAILURE;
        }
        pair->value++; // zvys pocet vyskytu
    }

    // Vytiskni pary
    htab_for_each(t, print_pairs);

#ifdef STATISTICS
    htab_statistics(t);
#endif

    // Uvolni tabulku
    htab_free(t);

    return EXIT_SUCCESS;
}

