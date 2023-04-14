/*
Autor: Milan Jakubec, Fakulta informačních technologií VUT v Brně
Příklad 2)
Datum: 14.4. 2023
*/

#include "htab.h"
#include "htab_private.h"

// htab_for_each - funkce projde vsechny pary v tabulce a na kazdou zavola funkci f
// @param t hash tabulka
// @param f funkce, ktera se ma zavolat na kazdou polozku
// @return void
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {

    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *item = t->arr_ptr[i];
        
        while (item != NULL) {
            f(&item->pair);
            item = item->next;
        }
    }
}

