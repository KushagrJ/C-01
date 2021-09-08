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


 * The #undef directive undefines a given #define.
   For eg., #define LIMIT 400
            ...
            #undef LIMIT
            #define LIMIT 500
 * Even if a macro isn't defined in the first place, it is still valid to
   undefine it. This is done mostly when the user is unsure whether a macro name
   has been used previously, and they undefine it to be on the safer side.
 * Macros with empty body are also considered to be defined. For eg., #define K
 * The scope of a #define macro extends from the point it is declared in a file
   until it is the subject of an #undef directive or until the end of file,
   whichever comes first.
 * Undefining predefined macros invokes undefined behaviour.

 * Some predefined macros :-
   __VA_ARGS__      - Variadic macro
   __DATE__         - String literal in the form "Mmm dd yyyy" representing the
                      date of preprocessing, as in Jun 22 2021
   __TIME__         - String literal in the form "hh:mm:ss" representing the
                      time of translation, as in 10:15:20
   __FILE__         - String literal representing the name of the current source
                      file
   __LINE__         - Integer value representing the current line number in the
                      current source file
   __STDC__         - Integer value representing whether the implementation
                      conforms to the C standard (1 for true)
   __STDC_HOSTED__  - Integer value representing whether the nvironment is
                      hosted (1 for true)
   __STDC_VERSION__ - Long integer value in the form "yyyymmL" representing the
                      version of the C standard the compiler conforms to.
 * __func__ is a string literal representing the name of the function containing
   it. __func__ is not a predefined macro and is rather a predefined identifier
   of the compiler, as the preprocessor does not know the name of the current
   function.


 * The #ifdef directive says that if the following macro name is defined, then
   follow all the directives & compile all the C code up to the next #else or
   #endif, whichever comes first.
   If there is an #else, then follow all the directives & compile all the C code
   up to the next #endif if the macro name isn't defined.
   For eg., (a) #define KJ
                #ifdef KJ
                    #include "header1.h"
                    #define SIZE 10
                #else
                    #include "header2.h"
                    #define SIZE 100
                #endif
                ...
            (b) #include <stdio.h>
                ...
                int main(void)
                {
                ...
                    #ifdef KJ
                        printf("Hello\n");
                    #else
                        printf("World\n");
                    #endif
                ...
 * The #ifndef directive also works with #else and #endif, similar to how #ifdef
   works, but #ifndef checks whether the following macro name is not defined.
   For eg., #ifndef SIZE
                #define SIZE 100
            #endif
 * The #if and #elif directives also work with #else and #endif similar to how
   #ifdef and #ifndef work, but #if and #elif are more like regular C if-else
   statements.
   #if and #elif are followed by constant integer expressions (similar rules to
   that of switch case labels apply) that are considered true if nonzero, and
   the relational & logical operators can also be used with them.
   For eg., #if SYS == 1
                #include "header1.h"
            #elif SYS == 2
                #include "header2.h"
            #else
                #include "header3.h"
            #endif
 * Also, instead of #ifdef KJ, #if defined KJ can also be used.
   Here, defined is a preprocessor operator that returns 1 if the argument is
   defined and 0 otherwise.
   The advantage of using #if defined over #ifdef is that #elif can also be used
   with #if defined.
 * These conditional structures can be nested as well.


 * The #line directive can be used to reset the line numbering and the file name
   as reported by the __LINE__ and __FILE__ macros.
   For eg., #line 1000        // Resets current line number to 1000.
            #line 10 "cool.c" // Resets current line number to 10, and current
                              // file name to cool.c
 * This directive is most commonly used when writing a compiler.
   For eg., line 12 of 121.c may go through the preprocessor, and now become
   line 183 of 121.tmp.cc
   If the C compiler finds an error in that line, then it would report that
   there is an error in line 183 of 121.tmp.cc, which isn't very useful.
   So, the #line directive can be used to make the error message report that the
   error was found at line 12 of 121.c


 * The #error directive causes the preprocessor to issue an error message that
   includes any text in the directive, and to halt the compilation process.
   For eg., #if __STDC_VERSION__ != 201112L
            #error Please use -std=c11
            #endif
            ...


 * The #pragma directive is used to place instructions for the compiler in the
   source code.
   These directives are machine-specific or operating-system-specific that may
   or may not apply to all machines and operating systems. These directives also
   might mean different things on different compilers.
 * The GCC compiler discourages the use of pragmas, as thay make the code
   non-portable.
 * For eg., a compiler can use the pragma '#pragma c17 on' to use the C17
   standard, instead of using command line arguments such as '-std=17'.


 * The term 'generic programming' indicates code that is not specific to a
   particular type, but which, once a type is specified, can be translated into
   code for that type.
 * C++ lets the user create generic algorithms in the form of templates that the
   compiler can then use to instantiate code automatically for a specified type.
 * In C, a generic selection expression can be used to select a value on the
   basis of the type of an expression (int, double, etc.).
 * The generic selection expression is not a preprocessor statement, but it is
   most commonly used as a part of a #define macro definition.
 * A generic selection expression is like a switch statement, except that the
   type of an expression rather than the value of an expression is matched to a
   label. The expression isn't evaluated, and only its type is determined.
 * For eg., #define M(x) _Generic((x), int: 0, float: 1, double: 2, default: 3)
            #define N(x) _Generic((x), char *: "ptr to char", default: "none")


 * Normally, a function call has overhead, i.e. it takes execution time to set
   up the call, pass arguments, jump to the function code, and return.
 * Function-like macros can be used to completely avoid overhead.
 * Using inline functions is another alternative to reduce overhead, and
   sometimes to avoid it completely as well.
   Making a function inline suggests that calls to the function be as fast as
   possible. The extent up to which such suggestions are effective is
   implementation-defined, similar to the register storage class.
   So, making a function inline may cause the compiler to replace the function
   call with inline code and/or perform some other sorts of optimizations, or it
   may have no effect at all.
 * A function with internal linkage (i.e. a static function) can be made inline.
   [Other uses of the keyword 'inline' are not discussed here, such as without
    'static' or with 'extern'.
    Inline functions have special rules about what 'extern' means.
    For non-inline and non-static functions, 'extern' is not needed as it is on
    by default.]
 * Usually, inline functions are defined before the first use in a file, thereby
   negating the use of a prototype.
   For eg., #include <stdio.h>
            ...
            inline static void eatline(void)
            {
                while (getchar() != '\n')
                    continue;
            }
            ...
            int main(void)
            ...
 * Taking the address of an inline function will make it non-inline, as an
   inline function doesn't have a separate block of code set aside for it.
 * An inline function should be short, because for a long function, the time
   consumed in calling the function is very less as compared to the time
   consumed in executing the body of the function. So, making a long function
   inline won't lead to great savings in time.
 * The simplest way to make an inline function accessible to multiple files
   within a multi-file program is to put the function definition in a header
   file and then include the header file in those files.
   Thus, an inline function is an exception to the practice of not placing
   executable code in a header file.
 * The keyword 'inline' is not a storage-class specifier, like static and
   extern, and is rather a function specifier.


 * '_Noreturn' is another function specifier which indicates that a function,
   upon completion, does not return to the calling function.
   [Functions with return type 'void' don't provide any value to the calling
    function, but they return to the calling function and the program continues]
 * The exit() function is an example of a _Noreturn function.


 * Any function declared in a header may be additionally implemented as a
   function-like macro defined in that header.
 * Any invocation of a library function that is implemented as a macro shall
   expand to code that evaluates each of its arguments exactly once, fully
   protected by parentheses where necessary.
 * This means that in-built function-like macros can be used like regular
   functions, even if the arguments are expressions involving side effects, as
   each of the arguments will be evaluated exactly once. Also, the expanded code
   will be fully protected by parentheses in order to avoid logical errors.
 * Thus, if SQUARE(X) in the above example was a library function's
   implementation as a macro, then SQUARE(++x) would not result in undefined
   behaviour.
 * Every implementation is supposed to provide an actual function for each
   library function implemented as a macro.
   Thus, the address of a library function can be taken even if it is also
   defined as a macro, as the address of the actual function will get taken.
   The use of #undef to remove any macro definition will ensure that the actual
   function is referred to.
   Additionally, enclosing the function name in parentheses in a function call
   will also ensure that the actual function is being called.
 * Also, library functions implemented as macros might not contain the sequence
   points that the corresponding function calls do.

 * Two exceptions to this rule are the functions getc() and putc().
   If getc() and putc() are implemented as macros, then they are allowed to
   evaluate fp more than once. So, the fp argument should never be an expression
   with side effects.
 * For this reason, it is safer to use fgetc() and fputc(), which are similar to
   getc() and putc(), except that fgetc() and fputc() cannot be implemented as
   macros.

 */
