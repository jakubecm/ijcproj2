/*
Autor: Milan Jakubec, Fakulta informačních technologií VUT v Brně
Příklad 2)
Datum: 14.4. 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htab.h"
#include "htab_private.h"

// htab_init - konstruktor tabulky pro n zaznamu
// @param n pocet zaznamu
// @return ukazatel na vytvorenou tabulku, NULL v pripade chyby
htab_t *htab_init(const size_t n) {
    htab_t *t = malloc(sizeof(htab_t));

    if (t == NULL) {
        return NULL; // alokace selhala
    }
    t->size = 0;
    t->arr_size = n;
    t->arr_ptr = malloc(n * sizeof(struct htab_item *));
    if (t->arr_ptr == NULL) {
        free(t);
        return NULL; // alokace selhala
    }
    for (size_t i = 0; i < n; i++) {
        t->arr_ptr[i] = NULL;
    }
    return t;
}
