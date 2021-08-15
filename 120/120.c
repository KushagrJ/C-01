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
   may be written in the directive lines, as they too will get deleted before
   preprocessing begins.
 * The preprocessor doesn't do any calculations. It just makes substitutions
   very literally.

 * Each #define directive has three parts. The first part is #define itself.
   The second part is the chosen abbreviation, known as a macro. The macro name
   must conform to the same naming rules as C identifiers follow.
   The third part (the remainder of the directive) is known as the replacement
   list or body.
 * Wherever the preprocessor finds the macro name not enclosed in double quotes,
   it replaces it with the body. This process of going from a macro to the final
   replacement is called macro expansion.
   For eg., #define TWO 2
            ...
            printf("TWO: %d\n", TWO);
            ...
            Here, the TWO inside printf()'s control string will not be replaced
            by 2, but the argument TWO will be.
            Thus, the output will be TWO: 2
 * More examples of #define :-
   #define TWO 2
   #define KJ "Program\
   ming is fun!"
   #define FOUR TWO*TWO   // Macro-nesting isn't supported by all compilers.
   #define PRINT_4 printf("%d\n", FOUR);
 * String literals using #define should be used carefully with printf(),
   scanf(), etc., as unknown conversion specifiers (such as %b) invoke undefined
   behaviour.
   For eg., #define DISCOUNT "10% before noon!"
            ...
            printf(DISCOUNT);   // Undefined behaviour.
            // fputs(DISCOUNT, stdout); and printf("%s", DISCOUNT); work fine.
            ...
 * String literals in general should be used carefully, as unknown escape
   sequences (such as \c) also invoke undefined behaviour.

   https://gcc.gnu.org/onlinedocs/cpp/Macros.html#Macros - See this as well

 */
