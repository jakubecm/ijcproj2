/*
Autor: Milan Jakubec, Fakulta informačních technologií VUT v Brně
Příklad 2)
Datum: 14.4. 2023
*/

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>


// htab_lookup_add - funkce hleda zaznam v tabulce, pokud tam neni, prida ho
// @param t hash tabulka
// @param key klic
// @return ukazatel na zaznam
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

        item->pair.key = malloc(strlen(key) + 1);
        if (item->pair.key == NULL) {
            free(item);
            return NULL;
        }
        strcpy((char*)item->pair.key, key);
        item->pair.value = 0;

        struct htab_item *tmp = t->arr_ptr[index];

        if(tmp == NULL)
        {
            t->arr_ptr[index] = item;
            item->next = NULL;
        }
        else
        {
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = item;
            item->next = NULL;
        }

        t->size++;
        return &(item->pair);


    }
    else return pair;

}
