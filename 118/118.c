// C17 Standard

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv)
{

    if (argc != 2)
        printf("Enter this: %s filename\n", argv[0]), exit(EXIT_FAILURE);

    FILE * fp;
    if ((fp = fopen(argv[1], "r")) == NULL)
        printf("Can't open %s\n", argv[1]), exit(EXIT_FAILURE);

    int c;
    unsigned long count = 0;
    while ((c = getc(fp)) != EOF)
        putc(c, stdout), count++;

    fclose(fp);

    printf("\nFile %s has %lu characters\n", argv[1], count);

    return 0;

}





/* Trivia

   [See 12.c's Trivia]

 * Redirection (discussed before) as a form of program-file communication is
   simple, but limited. For eg., if redirection is used for an interactive
   program that asks for book titles and then saves the complete listing in a
   file, then the interactive prompts will also get redirected to the file.
   Moreover, the user will be unable to see the questions that they are
   supposed to answer.

 * All file content is in binary form (zeroes and ones).
   1. If a file primarily uses the binary codes for characters (such as ASCII)
      to represent text, then it is a text file.
   2. If the binary values in the file represent machine-language code, numeric
      data, image/music/video encoding, etc., then it is a binary file.

 * C provides two ways of accessing a text file: binary mode and text mode.
   In the binary mode, each and every byte is accessible to a program, whereas
   in the text mode, the low level representation of things like end-of-line or
   end-of-file are mapped to C's view, which is equivalent to Unix or Linux's
   view. Thus, for Unix and Linux, the text view and the binary view are same.
   [For eg., a C program compiled on an older Macintosh would convert \r to \n
    when reading a file and convert \n to \r when writing to a file under the
    text mode.
    Similarly, for an MS-DOS platform, the conversions would be \r\n to \n and
    \n to \r\n, respectively.]

 * C programs automatically open 3 files on the user's behalf: the standard
   input, the standard output and the standard error output.
   The file pointers associated with these files are stdin, stdout and stderr.
   The standard input, by default, is the normal input device for a system,
   usually the keyboard.
   The standard output and the standard error output, by default, are the normal
   output device for a system, usually the display screen.
   [Redirection causes files to be recognized as the standard input or the
    standard output. The standard error output still goes to the screen, even
    after redirection.]


 * As discussed before, some operating systems don't allow the usage of argv[0].
 * The exit() function also closes any open files before terminating a program.

 * The fopen() function, prototyped in stdio.h, is used to open files.
   Its first argument is the address of the string containing the name of the
   file to be opened. Its second argument is a string (or more accurately, the
   string's address) identifying the mode in which the file is to be opened.
 * Different mode strings for fopen() :-
   1. "r"   - Open a text file for reading. The file must exist.
      "rb"  - Same, but in binary mode instead of text mode.
   2. "w"   - Open a text file for writing, truncating an existing file to zero
              length or creating the file if it does not exist.
      "wb"  - Same, but in binary mode instead of text mode.
   3. "a"   - Open a text file for writing, appending to the end of an existing
              file or creating the file if it does not exist.
      "ab"  - Same, but in binary mode instead of text mode.
   4. "r+"  - Open a text file for update (i.e. reading and writing both). The
              file must exist.
      "r+b" - Same, but in binary mode instead of text mode.
      "rb+" - Same as "r+b".
   5. "w+"  - Open a text file for update (i.e. reading and writing both), first
              truncating the file to zero length if it exists or creating the
              file if it does not exist.
      "w+b" - Same, but in binary mode instead of text mode.
      "wb+" - Same as "w+b".
   6. "a+"  - Open a text file for update (i.e. reading and writing both),
              appending to the end of an existing file or creating the file if
              it does not exist. The whole file can be read, but writing can
              only be appended.
      "a+b" - Same, but in binary mode instead of text mode.
      "ab+" - Same as "a+b".
   [C11 offers additional modes, such as "wx", "wbx", "w+x", "w+bx", etc., which
    are like the corresponding non-x modes, except they fail if the file already
    exists (instead of truncating it to zero length) and they open a file in
    exclusive mode, if possible. The exclusive mode keeps other programs or
    threads from accessing the file until the current process closes the file.]

 * After a file is successfully opened, fopen() returns a file pointer, which
   the other I/O functions can then use to specify the file.
   The file pointer is of type pointer-to-FILE.
   The file pointer doesn't point to the actual file. Instead, it points to a
   structure containing information about the file, including information about
   the buffer used for the file's I/O.
 * fopen() returns a null pointer if the file cannot be opened.

 * The getc() and putc() functions work similar to the getchar() and putchar()
   functions.
   getchar() is equivalent to getc(stdin) and putchar(c) is equivalent to
   putc(c, stdout).
 * Just like getchar(), getc() also returns EOF when it encounters end-of-file.

 * The fclose() function closes the file identified by the file pointer,
   flushing buffers as needed.
 * fclose() returns 0 if the file is closed successfully, and EOF if not.

 */
