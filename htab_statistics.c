
#include "htab.h"
#include "htab_private.h"
#include <stdio.h>



// výpočet a tisk statistik délky seznamů (min,max,avg) do stderr:
void htab_statistics(const htab_t * t){
    size_t min = 0; 
    size_t max = 0;
    
    for (size_t i = 0; i < t->arr_size; i++) {
        size_t count = 0;
        struct htab_item *item = t->arr_ptr[i]; // konkretni seznam itemu

        while (item != NULL) {
            count++;
            item = item->next;
        }
        // Count je spocitany, ted je cas porovnat
        if (min == 0){
            min = count; // pokud min jeste neni inicializovany, tak se nastavi na count prvniho seznamu
        }
        else if (count < min) {
            min = count;
        }
        
        if (count > max) {
            max = count;
        }
    }
    fprintf(stderr, "min: %zu, max: %zu, avg: %lu", min, max, (t->size / t->arr_size));

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
