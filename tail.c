/*
Příklad a)
Soubor: tail.c
Autor: Milan Jakubec 1 BIT FIT VUT
Prekladac: Apple clang 14.0
*/  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Makro na limitování délky řádku
#define LINE_LIMIT 4095

// Struktura pro kruhový buffer
typedef struct {
    int size; // Velikost bufferu
    int filled; // Zaplněnost bufferu
    int start; // Index začátku bufferu
    int end; // Index konce bufferu
    char **lines; // Pole ukazatelů na řádky
} circular_buffer;

// Funkce pro vytvoření kruhového bufferu
// @params n - velikost bufferu
// @return - ukazatel na vytvořený buffer
circular_buffer * cb_create(int n){

    circular_buffer * cb = malloc(sizeof(circular_buffer));
    if(cb == NULL){
        fprintf(stderr, "Error: Can't allocate memory for buffer.\n");
        exit(1);
    }

    cb->lines = malloc(n * sizeof(char *));
    if(cb->lines == NULL){
        fprintf(stderr, "Error: Can't allocate memory for lines in buffer.\n");
        exit(1);
    }
    cb->size = n;
    cb->filled = 0;
    cb->start = 0;
    cb->end = 0;
    return cb;
}

// Funkce pro vložení řádku do bufferu
// @params cb - ukazatel na buffer
// @params line - řádek, který se má vložit

void cb_put(circular_buffer *cb, char *line){

    if(cb->filled == cb->size){
        free(cb->lines[cb->start++]); // uvolnění paměti pro přepsaný řádek
        cb->start %= cb->size; // posun na další prvek
    }
    else{
        cb->filled++;
    }
    cb->lines[cb->end++] = line;
    cb->end %= cb->size; // posun na další prvek
}

// Funkce pro získání řádku z bufferu
// @params cb - ukazatel na buffer
// @return - řádek, který se má získat
char * cb_get(circular_buffer *cb){

    if(cb->filled == 0){
        return NULL;
    }
    char *line = cb->lines[cb->start++];
    cb->start %= cb->size; // posun na další prvek
    cb->filled--;
    return line;
}

// Funkce pro uvolnění paměti bufferu
// @params cb - ukazatel na buffer
void cb_free(circular_buffer *cb){

    for(int i = 0; i < cb->size; i++){
        free(cb->lines[i]);
    }
    free(cb->lines);
    free(cb);
}

int main(int argc, char *argv[]){

    char *filename = NULL;
    int n = 10;

    if(argc > 4){
        fprintf(stderr, "Error: Too many arguments.\n");
        exit(1);
    }

    if (argc == 4)
    {
        if (strcmp(argv[1], "-n") == 0)
        {
            n = strtol(argv[2], NULL, 10);
            if (n <= 0)
            {
                fprintf(stderr, "Error: Invalid number of lines.\n");
                exit(1);
            }
        }
        else
        {
            fprintf(stderr, "Error: Invalid argument.\n");
            exit(1);
        }
        filename = argv[3];
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-n") == 0)
        {
            n = strtol(argv[2], NULL, 10);
            if (n <= 0)
            {
                fprintf(stderr, "Error: Invalid number of lines.\n");
                exit(1);
            }
        }
        else
        {
            fprintf(stderr, "Error: Invalid argument.\n");
            exit(1);
        }
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-n") == 0)
        {
            fprintf(stderr, "Error: Missing number of lines.\n");
            exit(1);
        }
        else
        {
            filename = argv[1];
        }
    }

    FILE * file = NULL;
    if(filename != NULL){
        file = fopen(filename, "r");
        if(!file){
            fprintf(stderr, "Error: Can't open file.\n");
            exit(1);
        }
    }
    else{
        file = stdin;
    }

    circular_buffer *cb = cb_create(n);
    if (cb == NULL)
    {
        fprintf(stderr, "Error: Can't allocate memory for buffer.\n");
        exit(1);
    }

    // Načtení řádků
    char *line = malloc(LINE_LIMIT * sizeof(char));
    int overflowFlag = 0;

    while (fgets(line, LINE_LIMIT, file) != NULL)
    {
        size_t read = strlen(line);

        if (read > 0 && line[read - 1] != '\n')
        {
            if (overflowFlag == 0)
            {
                fprintf(stderr, "Warning: One of the lines is too long, it will be truncated to %i.\n", LINE_LIMIT);
                // Nastav flag na 1, aby se warning znovu nevypisoval
                overflowFlag = 1;
            }
            line[LINE_LIMIT - 1] = '\n'; // Na konec přidat znak konce řádku
            // Na indexu line[LINE_LIMIT] přidávat nic nemusím, protože null terminator tam za mě dal už fgets.
            int c;
            while ((c = fgetc(file)) != '\n' && c != EOF)
            {
                // Zahodit zbytek řádku
            }
        }

        cb_put(cb, line);
        line = malloc(LINE_LIMIT * sizeof(char)); // Allocate new memory for the next line
    }
    free(line); // Free the last allocated memory after the loop

    // Vypsání řádků
    char *line_to_print = cb_get(cb);
    while(line_to_print != NULL){
        printf("%s",line_to_print);
        line_to_print = cb_get(cb);
    }

    // Uvolnění paměti
    cb_free(cb);

    if(filename != NULL){
        fclose(file);
    }

    return 0;
}

