// C17 Standard

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * modified_fgets(char *, const int, FILE *);
void wrap_line(char *, const int);


int main(int argc, char ** argv)
{

    if (argc != 2)
        printf("Enter this: %s filename\n", argv[0]), exit(EXIT_FAILURE);

    FILE * in;
    if ((in = fopen(argv[1], "r")) == NULL)
        fprintf(stderr, "Can't open %s!\n", argv[1]), exit(EXIT_FAILURE);

    FILE * out;
    if ((out = fopen("119_OUT.txt", "w")) == NULL)
        fprintf(stderr, "Can't create output file!\n"), exit(EXIT_FAILURE);

    char s[1024];
    while (modified_fgets(s, 1024, in) != NULL)
        wrap_line(s, 80), fprintf(out, "%s\n", s);

    fclose(in);
    fclose(out);

    return 0;

}


char * modified_fgets(char * s, const int n, FILE * fp)
{

    char * returnValue;
    returnValue = fgets(s, n, fp);

    int i = 0;
    int c;

    if (returnValue != NULL)
    {
        while ((s[i] != '\n') && (s[i] != '\0'))
            i++;
        if (s[i] == '\n')
            s[i] = '\0';
        else // s[i] == '\0' (i.e. there are extra characters in the line).
            while (((c = getc(fp)) != '\n') && (c != EOF))
                continue;
    }

    return returnValue;

}


// This function wraps a single line, terminated by '\0' instead of '\n'.
// wrapColumn should be >= the length of the longest word.
// '\t' should not have been used in the line to be wrapped.
void wrap_line(char * s, const int wrapColumn)
{

    int lastWrap = 0;
    int stringLength = strlen(s);
    int lastSpace = -1;

    for (int i = 0; i < stringLength; i++)
    {
        if (s[i] == ' ')
            lastSpace = i;

        if (i - lastWrap == wrapColumn)
        {
            if (lastSpace == -1)
                fprintf(stderr, "Too long words!\n"), exit(EXIT_FAILURE);
            s[lastSpace] = '\n';
            lastWrap = lastSpace + 1;
            lastSpace = -1;
        }
    }

}





/* Trivia

 * Each file is opened/closed independently of the other.
 * The same file pointer can be used for different files, provided those files
   are not open at the same time.

 * fprintf() and fscanf() work similar to printf() and scanf(), but they
   require a file pointer as an additional first argument.

 * When a file is opened in the append mode, text can only be added to the end
   of the file, but the whole file can be read.
   In order to read the file from the start after something has been appended to
   it, the rewind() function can be used. For eg., rewind(fp);
 * Basically, rewind() sets the cursor (or technically, the file pointer itself)
   to the beginning of the file. It is equivalent to
   fseek(stream, 0L, SEEK_SET); (discussed below), but unlike fseek(), rewind()
   does not not provide an error code (i.e. the error indicator of the stream is
   also cleared), so the user can not know if it failed.

 * The fseek() function can be used to treat a file like an array and move the
   file pointer directly to any particular byte in a file opened by fopen()
   (i.e. basically the same as moving the cursor in a text editor). It returns 0
   if everything was okay, or -1 if there was an error, such as attempting to
   move past the bounds of the file.
 * The ftell() function returns the current position in a file as a long int.
   For eg., long x = ftell(fp);

 * The first argument to fseek() is a file pointer to a file opened by fopen().
   The second argument is a long int value called the offset. This argument
   tells how far to move from the starting point. This doesn't always mean
   number of bytes.
   The third argument is the mode, and it identifies the starting point. The
   stdio.h header file specifies SEEK_SET (beginning of file), SEEK_CUR (current
   position) and SEEK_END (end of file) as the modes for fseek().

 * In the binary mode, implementations need not support SEEK_END.
   In the text mode, the only combinations that are guaranteed to work are
   fseek(stream, 0L, SEEK_SET), fseek(stream, 0L, SEEK_CUR),
   fseek(stream, 0L, SEEK_END) and fseek(stream, ftellpos, SEEK_SET), where
   ftellpos is a value returned by ftell().

 * The fgetpos() and fsetpos() functions use the type fpos_t to indicate the
   positions, instead of long int. fpos_t is not a fundamental data type,
   similar to size_t, and is defined in terms of other types.
 * For eg., fgetpos(stream, pos) places an fpos_t value (i.e. the current
   position of the file pointer) in the location pointed to by pos, and
   fsetpos(stream, pos) takes an fpos_t value from the position pointed to by
   pos and sets the file pointer to the location indicated by that value.
 * Both fgetpos() and fsetpos() return 0 for success and a non-zero value for
   failure.

 */
