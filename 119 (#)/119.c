// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdlib.h>


char * modified_fgets(char *, const int, FILE *);
void wrap_line(char *, const int);


int main(int argc, char ** argv)
{

    if (argc != 2)
    {
        printf("Enter this: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE * in;
    if ((in = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Can't open %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE * out;
    if ((out = fopen("119_OUT.txt", "w")) == NULL)
    {
        fprintf(stderr, "Can't create output file!\n");
        exit(EXIT_FAILURE);
    }

    char s[1024];
    while (modified_fgets(s, 1024, in) != NULL)
        wrap_line(s, 80), fprintf(stdout, "%s\n", s);

    fclose(in);
    fclose(out);

    return 0;

}


char * modified_fgets(char * s, const int n, FILE * fp)
{

    char * returnValue = fgets(s, n, fp);

    int i = 0;
    int c;

    if (returnValue)
    {
        while ((s[i] != '\n') && (s[i] != '\0'))
            i++;

        if (s[i] == '\n')
        {
            s[i] = '\0';
        }

        else // s[i] == '\0' (i.e. there are extra characters in the line).
        {
            while (((c = getc(fp)) != '\n') && (c != EOF))
                continue;
        }
    }

    return returnValue;

}


// This function wraps a single line, terminated by '\0' instead of '\n'.
// wrapColumn should be >= the length of the longest word.
// '\t' should not have been used in the line to be wrapped.
void wrap_line(char * s, const int wrapColumn)
{

    int lastWrap = 0;
    int lastSpace = -1;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ' ')
            lastSpace = i;

        if (i - lastWrap == wrapColumn)
        {
            if (lastSpace == -1)
            {
                fprintf(stderr, "Too long words!\n");
                exit(EXIT_FAILURE);
            }
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

 * When a file is opened in the read+append mode, text can only be added to the
   end of the file, but the whole file can be read.
   [In the append mode, repositioning operations such as fseek(), fsetpos() and
    rewind() are ignored.
    In the read+append mode, repositioning operations such as fseek(), fsetpos()
    and rewind() affect the next reading operations, but writing operations move
    the current position back to the end of the file.]
 * In order to read the file from the start, the rewind() function can be used.
   For eg., rewind(fp);
   Basically, rewind() sets the cursor (or technically, the file position
   indicator's current position) to the beginning of the file. It is equivalent
   to fseek(fp, 0L, SEEK_SET); (discussed below), but unlike fseek(), rewind()
   does not not provide an error code (i.e. the error indicator of the stream is
   also cleared), so the user can not know if it failed.

 * The fseek() function can be used to treat a file like an array and move the
   current position directly to any particular byte in a file opened by fopen()
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

 * In the binary mode, implementations need not support SEEK_END, and may invoke
   undefined behaviour if used.
 * In the text mode, the only combinations that are guaranteed to work are
   fseek(fp, 0L, SEEK_SET), fseek(fp, 0L, SEEK_CUR), fseek(fp, 0L, SEEK_END) and
   fseek(fp, ftellpos, SEEK_SET), where ftellpos is a value returned by ftell().

 * For eg., on Windows (where the text mode and the binary mode are different
   from each other), the return value of ftell() in the text mode contains
   unspecified information, properly usable only by fseek() to return the file
   position indicator to its position at the time of that ftell() call.
   But, in the binary mode (on any platform), it is guaranteed that the return
   value of ftell() is the number of characters (or the number of bytes) from
   the beginning of the file.
 * Thus, seeking around a text file manually (on any platform) should always be
   done in the binary mode (without the usage of SEEK_END), and the different
   line endings (\n, \r, \r\n) should be dealt with manually.

 * The fgetpos() and fsetpos() functions use the type fpos_t to indicate the
   positions, instead of long int. fpos_t is not a fundamental data type,
   similar to size_t, and is defined in terms of other types.
 * For eg., fgetpos(fp, pos) places an fpos_t value (i.e. the current position
   of the file position indicator) in the memory location pointed to by pos, and
   fsetpos(fp, pos) takes an fpos_t value from the memory location pointed to by
   pos and sets the file position indicator to the position indicated by that
   value.
 * Both fgetpos() and fsetpos() return 0 for success and a non-zero value for
   failure.


 * Normally, the first step in using standard I/O is to use fopen() to open a
   file. stdin, stdout and stderr files are opened automatically.
 * fopen() not only opens a file but sets up two buffers (input & output) and
   a structure containing data about the file & the buffers.
 * fopen() then returns a pointer to this structure so that other functions know
   where to find it.
 * If a file is opened in the text mode, then a text stream is opened, and if
   it is opened in the binary mode, then a binary stream is opened.

 * When an input function is called on an input stream, data is copied from the
   file to the input buffer, and then into the program. Also, the current
   position and the number of bytes copied are set in the structure pointed to
   by the file pointer.
 * When an input function finds that it has read all the characters in the
   buffer, it requests that the next buffer-sized chunk of data be copied from
   the file into the buffer. In this manner, the input functions can read all
   the file contents up to the end of the file.

 * In a similar manner, output functions write to a buffer. When the buffer is
   filled, the data is copied to the file.


 * The int ungetc(int c, FILE * fp) function pushes the character specified by
   c back onto the input stream.
   For eg., the user can use getchar() or getc() to read characters until a
   colon is read and then use ungetc() to place the colon back in the input
   stream.
   The C standard guarantees only one push back at a time.
   If successful, ungetc() returns the character that was pushed back.
   Otherwise, EOF is returned and the stream remains unchanged.

 * The int fflush(FILE * fp) function causes any unwritten data in the output
   buffer to be sent to the file identified by fp. This process is called
   flushing a buffer.
   Calling fflush() on an input stream invokes undefined behaviour.
   fflush() can be used on an update stream (i.e. reading+writing), provided
   that the most recent operation was not input.
   If successful, fflush() returns 0. Otherwise, EOF is returned.

 * The int setvbuf(FILE * fp, char * buf, int mode, size_t size) function
   sets up an alternative buffer to be used by the standard I/O functions.
   It is called after the file has been opened and before any other operations
   have been performed on the stream.
   The pointer fp identifies the stream, and buf points to the storage to be
   used. For eg., an array of 1024 characters can be declared and its address
   can be passed to setvbuf() as the argument buf. Passing NULL as buf makes the
   function allocate a buffer itself.
   The size variable tells the function how big the array is. It is ignored by
   GCC if buf == NULL.
   The mode is selected from the following choices: _IOFBF (buffer flushed when
   full), _IOLBF (buffer flushed when full or when a newline is written) and
   _IONBF (non-buffered).
   If successful, setvbuf() returns 0. Otherwise, a non-zero value is returned.


 * As discussed before, when the data is stored in a file using the same
   representation that the program uses, it is said that the file is a binary
   file.
   The text mode and the binary mode can both be used to open text files and
   binary files. But, generally, a binary file is opened in the binary mode and
   a text file is opened in either the text mode or the binary mode.
   For binary files, the functions fwrite() and fread() can be used.

 * The size_t fwrite(const void * ptr, size_t size, size_t nmemb, FILE * fp)
   function writes binary data to a file.
   The pointer ptr is the address of the chunk of data to be written.
   size represents the size, in bytes, of the chunks to be written.
   nmemb represents the number of chunks to be written.
   If successful, fwrite() returns the number of items successfully written. If
   the return value is less than nmemb, then it means that an error occurred.

 * The size_t fread(void * ptr, size_t size, size_t nmemb, FILE * fp) function
   reads binary data from a file.
   This function is used to read data that was written to a file using fwrite().
   If successful, fread() returns the number of items successfully read. If the
   return value is less than nmemb, then it means that either an error occurred
   or end-of-file was reached.


 * When the standard input functions return EOF, this usually means that they
   have reached the end of a file. However, it can also indicate that a read
   error has occurred.
   The int feof(FILE * fp) and the int ferror(FILE * fp) functions are used to
   distinguish between the two possibilities.
 * The feof() function returns a non-zero value if the last input call detected
   the end-of-file, and it returns 0 otherwise.
 * The ferror() function returns a non-zero value if a read or write error has
   occurred, and it returns 0 otherwise.


   [Study programs involving the use of setvbuf(), fread() and fwrite() later]

 */
