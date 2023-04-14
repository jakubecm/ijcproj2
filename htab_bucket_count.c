/*
Autor: Milan Jakubec, Fakulta informačních technologií VUT v Brně
Příklad 2)
Datum: 14.4. 2023
*/

#include "htab.h"
#include "htab_private.h"


// htab_bucket_count
// @param t hash tabulka
// @return kapacita zaznamu v tabulce
size_t htab_bucket_count(const htab_t * t) {
    return t->arr_size;
}
