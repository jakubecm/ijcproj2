/*
Autor: Milan Jakubec, Fakulta informačních technologií VUT v Brně
Příklad 2)
Datum: 14.4. 2023
*/

#include "htab.h"

// struktura pro zaznamy v tabulce
struct htab {
    size_t size; // aktualni pocet zaznamu
    size_t arr_size; // velikost pole
    struct htab_item** arr_ptr; // ukazatel na pole ukazatelu na prvky
};
// struktura pro prvky v tabulce
struct htab_item {
    struct htab_pair pair;
    struct htab_item* next;
};
