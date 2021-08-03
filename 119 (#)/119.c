// C17 Standard

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static char * modified_fgets(char *, const int, FILE *);
static void wrap_line(char *, const int);


int main(int argc, char ** argv)
{

    if (argc != 2)
        printf("Enter this: %s filename\n", argv[0]), exit(EXIT_FAILURE);

    FILE * in;
    if ((in = fopen(argv[1], "r")) == NULL)
        fprintf(stderr, "Can't open %s\n", argv[1]), exit(EXIT_FAILURE);

    FILE * out;
    if ((out = fopen("119_OUT.txt", "w")) == NULL)
        fprintf(stderr, "Can't create output file\n"), exit(EXIT_FAILURE);

    char s[1024];
    while (modified_fgets(s, 1024, in) != NULL)
        wrap_line(s, 80), fprintf(out, "%s\n", s);

    if ((fclose(in) != 0) || (fclose(out) != 0))
        fprintf(stderr, "Error in closing files\n");

    return EXIT_SUCCESS;

}


// This function reads a line that is either too long or is terminated by '\n'.
static char * modified_fgets(char * s, const int n, FILE * fp)
{

    char * returnValue;
    returnValue = fgets(s, n, fp);

    int i = 0;

    if (returnValue != NULL)
    {
        while ((s[i] != '\n') && (s[i] != '\0'))
            i++;
        if (s[i] == '\n')
            s[i] = '\0';
        else // s[i] == '\0' (i.e. there are extra characters in the line).
            while (getc(fp) != '\n')
                continue;
    }

    return returnValue;

}


// This function wraps a single line, terminated by '\0' instead of '\n'.
// wrapColumn should be >= the length of the longest word.
// '\t' should not have been used in the line to be wrapped.
static void wrap_line(char * s, const int wrapColumn)
{

    int lastWrap = 0;

    for (int i = 0; i < (int) strlen(s); i++)
        if (i - lastWrap == wrapColumn)
            for (int k = i; k > 0; k--)
                if (s[k] == ' ')
                {
                    s[k] = '\n';
                    lastWrap = k+1;
                    break;
                }

}





/* Trivia

 *

 */
