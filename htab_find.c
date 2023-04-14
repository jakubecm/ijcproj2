/*
Autor: Milan Jakubec, Fakulta informačních technologií VUT v Brně
Příklad 2)
Datum: 14.4. 2023
*/

#include "htab.h"
#include "htab_private.h"

// htab_find - funkce pro nalezeni zaznamu key v tabulce
// @param t hash tabulka
// @param key klic
// @return ukazatel na zaznam s klicem key, pokud ho v tabulce neni, vraci NULL
htab_pair_t * htab_find(const htab_t * t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size; // index do pole ukazatelu
    struct htab_item *item = t->arr_ptr[index]; 
    while (item != NULL) { // hledani shody
        if (strcmp(item->pair.key, key) == 0) {
            return &item->pair; // shoda nalezena
        }
        item = item->next;
    }
    return NULL; // shoda nenalezena
}

/*
      +----------+
      | size     | // aktuální počet záznamů [(key,data),next]
      +----------+
      | arr_size | // velikost pole ukazatelů (počet položek)
      +----------+
      | arr_ptr  | // ukazatel na dynamicky alokované pole ukazatelů
      +----------+
        |
        V
      +---+
      |ptr|-->[(key,data),next]-->[(key,data),next]-->[(key,data),next]--|
      +---+
      |ptr|--|
      +---+
      |ptr|-->[(key,data),next]-->[(key,data),next]--|
      +---+
      |ptr|--|
      +---+
      
*/
