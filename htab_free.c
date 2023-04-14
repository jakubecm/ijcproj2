/*
Autor: Milan Jakubec, Fakulta informačních technologií VUT v Brně
Příklad 2)
Datum: 14.4. 2023
*/

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

// htab_free - funkce uvolni pamet, ktera byla alokovana pro tabulku
// @param t hash tabulka
// @return void
void htab_free(htab_t * t){
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}
