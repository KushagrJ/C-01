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
 * The scope of a #define macro extends from the point it is declared in a file
   until it is the subject of an #undef directive or until the end of file,
   whichever comes first.
 * Undefining predefined macros such as __DATE__ and __FILE__ invokes undefined
   behaviour.

   https://gcc.gnu.org/onlinedocs/cpp/Macros.html#Macros - See this as well

 */
