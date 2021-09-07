// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>


#define PSQR(X) printf("The square of %d is %d\n", X, ((X)*(X)))


int main(void)
{

    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);

    PSQR(num);

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
 * A directive can appear anywhere in a source file.
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
 * Any valid identifier name can be used as the name of a macro, even if it is a
   C keyword, as the preprocessor does not know anything about keywords.
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
   #define PRINT_4 printf("%d\n", FOUR)
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

 * The body of a macro is considered to be a string of tokens rather than a
   string of individual characters by the preprocessor.
   For eg., in #define FOUR 2*2, there is one token (2*2), but in
            #define SIX 2 * 3, there are 3 tokens (2, * and 3).
   [The character string interpretation views the spaces as part of the body,
    whereas the token interpretation views the spaces as separators between the
    tokens of the body]
   [The C compiler takes a more complex view of tokens than the preprocessor
    does. The compiler understands the rules of C and doesn’t necessarily
    require spaces to separate tokens. For eg., the C compiler would view 2*2 as
    three tokens because it recognizes that each 2 is a constant expression and
    that * is an operator.]
 * Thus, #define SIX 2 * 3 and #define SIX 2    *    3 are the same, but
   #define SIX 2*3 is different.
   Redefinition without first using #undef is allowed only if the new definition
   duplicates the old, as per the C Standard.

 * FOUR, SIX, etc. are known as object-like macros, because they resemble data
   objects when used.
 * By using arguments with #define, the user can create function-like macros
   that look and act much like functions.
   For eg., #define SQUARE(X) X*X
            #define PR(X) printf("The result is %d.\n", X)
 * A macro argument doesn't work exactly like a function argument.
   For eg., (a) If SQUARE() were a function, then SQUARE(5+2) would've returned
                49, but since SQUARE() is a macro defined as X*X, SQUARE(5+2) is
                replaced by 5+2*5+2, which the compiler later evaluates to 17.
                This can be solved by using #define SQUARE(X) (X)*(X).
            (b) Now, since SQUARE() is defined as (X)*(X), 100/SQUARE(2) would
                be replaced by 100/(2)*(2), which would later evaluate to 100.
                Thus, to solve this as well, SQUARE(X) should be defined as
                ((X)*(X)).
            (c) Finally, SQUARE(++x) would be replaced by ((++x)*(++x)) and
                invoke undefined behaviour, no matter how many parentheses are
                used in the body. [Similarly for others]
                Thus, increment/decrement operators shouldn't be used with
                macros.

 * Macros with empty body (#define KJ or #define sum(a)) don't produce any code,
   as the macro name will get replaced by empty text.
 * For eg., #define sum(x)
            ...
            sum(22); // Will get replaced by ; in the program.

 * For eg., #define PSQR(X) printf("The square of X is %d.\n", ((X)*(X)))
   PSQR(8); would print The square of X is 64., as the X inside double quotes is
   treated as ordinary text, not as a token that can be replaced. One way to
   print The square of 8 is 64. instead of The square of X is 64. is by using
   #define PSQR(X) printf("The square of %d is %d.\n", X, ((X)*(X)))
 * But, this can also be done by another method, i.e. by using the # operator.
   Within the body of a function-like macro, the # symbol becomes a
   preprocessing operator that converts tokens into strings. For eg., if X is a
   macro parameter, then #X is that parameter converted to "X". This process is
   called stringizing. Thus, in order to print The square of 8 is 64.,
   #define PSQR(X) printf("The square of " #X " is %d.\n", ((X)*(X))) can also
   be used. PSQR(8); will now be replaced by
   printf("The square of " "8" " is %d.\n", ((8)*(8))); in the program.

 * The ## operator combines two tokens into a single token. It can be used in
   the bodies of object-like and function-like macros.
   For eg., #define KJ(n) x ## n
            ...
            int KJ(1) = 22;   // becomes int x1 = 22;
            ...

 * Functions such as printf() accept a variable number of arguments.
   Creating user-defined functions that accept a variable number of arguments is
   discussed later.

 * A macro that accepts a variable number of arguments can be created by using
   an ellipsis as the final argument.
   Then, the predefined macro __VA_ARGS__ can be used in its body to indicate
   what will be substituted for the ellipsis.
 * For eg., #define PR(...) printf(__VA_ARGS__)


 * When the preprocessor spots an #include directive, it looks for the following
   file and replaces the #include directive with the text from that file.
 * On a UNIX (or similar) system, the angle brackets (<stdio.h>) tell the
   preprocessor to look for the file in one or more standard system directories.
   The double quotation marks ("my_header.h") tell it to first look in the
   current directory (or the location described - "/home/my_header.h"), and then
   look in the standard system directories.
 * The .h suffix is conventionally used for header files.

 * The most common header files contain manifest constants, function-like
   macros, function prototypes, structure declarations, typedef statements, etc.

 */
