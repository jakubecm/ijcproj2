/*
Autor: Milan Jakubec, Fakulta informačních technologií VUT v Brně
Příklad 2)
Datum: 14.4. 2023
*/

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

// Funkce cisti tabulku a uvolni pamet
// htab_clear
// @param t hash tabulka
// @return void
void htab_clear(htab_t * t){

    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *item = t->arr_ptr[i];
        while (item != NULL) {
            struct htab_item *next = item->next;
            free((char *)item->pair.key);
            free(item);
            item = next;
        }
        t->arr_ptr[i] = NULL;
    }
    t->size = 0;
}
