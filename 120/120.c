// C17 Standard

#include <stdio.h>


int main(void)
{

    return 0;

}





/* Trivia

 * The C preprocessor looks at a program before it is compiled.
   Following the given directives, it replaces the symbolic abbreviations in a
   program.
   Basically, it takes some text and converts it to other text.

 * The compiler puts a program through some translation phases before jumping
   into preprocessing.
 * First, the compiler maps characters appearing in the source code to the
   character set.
 * Second, the compiler locates each instance of a backslash followed by a
   newline character in the source code (i.e. the ENTER key, not '\n'), and
   deletes them. This is useful because preprocessor directives are required to
   be one logical line long.
   [For eg., two physical lines such as printf("Hello, \
                                        World!\n");
             are converted to a single logical line printf("Hello, World\n");]
 * Third, the compiler breaks the text into a sequence of preprocessing tokens
   (i.e. groups separated from each other by whitespace) and sequences of
   whitespace & comments. Also, each comment is replaced by one space character.

 * A C preprocessor directive begins with the # symbol. The # can appear at the
   leftmost column of a line or can be preceeded by whitespace. Also, there may
   be whitespace between the # and the remainder of the directive.
 * A directive can appear anywhere in a source file, and the definition holds
   from its place of appearance to the end of the file.
 * Preprocessor directives run until the first newline following the #. However,
   since the combination of \ and ENTER is deleted before preprocessing, it can
   be used to spread the directive over several physical lines. Also, comments
   may be written in the directive lines, as they too will get deleted.

   https://gcc.gnu.org/onlinedocs/cpp/Macros.html#Macros - See this as well

 */
