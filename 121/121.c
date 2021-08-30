// C17 Standard

#include <stdio.h>


int main(void)
{

    return 0;

}





/* Trivia

 * The #undef directive undefines a given #define.
   For eg., #define LIMIT 400
            ...
            #undef LIMIT
            #define LIMIT 500
 * Even if a macro isn't defined in the first place, it is still valid to
   undefine it. This is done mostly when the user is unsure whether a macro name
   has been used previously, and they undefine it to be on the safer side.
 * Macros with empty body are also considered to be defined(for eg., #define K).
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

 */
