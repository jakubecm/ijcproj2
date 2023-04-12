

#include <stdio.h>

int read_word(char *s, int max, FILE *f){

    int c;
    int i = 0;
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
                fprintf(stderr, "Warning: word is too long, it will be truncated to %d characters.", max - 1);
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