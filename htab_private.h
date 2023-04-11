
#include "htab.h"


struct htab {
    size_t size; // aktualni pocet zaznamu
    size_t arr_size; // velikost pole
    struct htab_item** arr_ptr; // ukazatel na pole ukazatelu na prvky
};

struct htab_item {
    struct htab_pair pair;
    struct htab_item* next;
};