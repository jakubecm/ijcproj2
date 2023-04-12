


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htab.h"
#include "htab_private.h"

// htab_init -- konstruktor tabulky
// Vytvoří tabulku s počtem záznamů n.
// Vrací ukazatel na vytvořenou tabulku, NULL v případě chyby.

htab_t *htab_init(const size_t n) {
    htab_t *t = malloc(sizeof(htab_t));

    if (t == NULL) {
        return NULL; // alokace selhala
    }
    t->size = 0;
    t->arr_size = n;
    t->arr_ptr = malloc(n * sizeof(struct htab_item *));
    for (size_t i = 0; i < n; i++) {
        t->arr_ptr[i] = NULL;
    }
    return t;
}
