

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

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
