/*
Autor: Milan Jakubec, Fakulta informačních technologií VUT v Brně
Příklad 2)
Datum: 14.4. 2023
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

//read_word - funkce nacte jedno slovo ze souboru f
// @param s ukazatel na retezec, kam se ma slovo ulozit
// @param max maximalni delka slova
// @param f soubor, ze ktereho se ma slovo nacist
// @return delka nacteneho slova, EOF pokud se nepodarilo nic nacist
int read_word(char *s, int max, FILE *f){

    int c = 0;
    int i = 0;
    static bool warning = false;
    while ((c = fgetc(f)) != EOF)
    {
        if (isspace(c))
        {
            if (i > 0)
            {
                break;
            }
        }
        else
        {
            if (i < max - 1)
            {
                s[i] = c;
                i++;
            }
            else
            {
                if(!warning){
                    fprintf(stderr, "Warning: word is too long, it will be truncated to %d characters.\n", max - 1);
                    warning = true;
                }
                // Zahod zbytek slova
                while (!isspace(fgetc(f))){
                    ;
                }
                break;
            }
        }
    }
    s[i] = '\0';
    if (i == 0 && c == EOF)
    {
        return EOF;
    }
    return i;
}
