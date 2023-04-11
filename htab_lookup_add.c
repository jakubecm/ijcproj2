


/*
htab_pair_t htab_lookup_add(htab_t *t, htab_key_t key);
V tabulce  t  vyhledá záznam odpovídající řetězci  key  a
- pokud jej nalezne, vrátí ukazatel na záznam
- pokud nenalezne, automaticky přidá záznam a vrátí ukazatel
*/

#include "htab.h"
#include "htab_private.h"
#include "htab_find.c"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {

    htab_pair_t * pair = htab_find(t, key);
 
    if(pair == NULL)
    {
        size_t index = htab_hash_function(key) % t->arr_size;
        struct htab_item *item = t->arr_ptr[index];
        item = malloc(sizeof(struct htab_item));
        if (item == NULL) {
            return NULL;
        }
        item->pair.key = key;
        item->pair.value = 0;
        item->next = t->arr_ptr[index];
        t->arr_ptr[index] = item;
        t->size++;
        return &item->pair;
    }
    else return pair;

}