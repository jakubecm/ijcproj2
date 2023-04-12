


#include "htab.h"
#include "htab_private.h"

//htab_erase(t,key)       zrušení záznamu se zadaným klíčem (úspěch:true)

bool htab_erase(htab_t * t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item *previous = NULL; // pomocny ukazatel na predchozi prvek
    struct htab_item *item = t->arr_ptr[index]; // ukazatel na prvni prvek v seznamu
    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            if (previous == NULL) {
                t->arr_ptr[index] = item->next; // pokud je hledany prvek v seznamu, tak se posune ukazatel na prvni prvek v seznamu na dalsi prvek
            } else {
                previous->next = item->next;
            }
            free(item); // uvolneni pameti konkretniho prvku
            t->size--; // zmena aktualniho obsazeni o jedna
            return true;
        }
        previous = item;
        item = item->next; 
    }
    return false;
}