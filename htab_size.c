/*
Autor: Milan Jakubec, Fakulta informačních technologií VUT v Brně
Příklad 2)
Datum: 14.4. 2023
*/

#include "htab.h"
#include "htab_private.h"

// htab_size - funkce vrati pocet zaznamu v tabulce
// @param t hash tabulka
// @return pocet zaznamu v tabulce
size_t htab_size(const htab_t * t) {
    return t->size;
}
