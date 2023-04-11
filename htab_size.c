


#include "htab.h"
#include "htab_private.h"

// Vrati aktualni pocet zaznamu v tabulce
size_t htab_size(const htab_t * t) {
    return t->size;
}