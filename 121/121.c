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

 */
