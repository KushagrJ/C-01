// C17 Standard

#include <stdio.h>


int main(int argc, char ** argv)
// or int main(int argc, char * argv[])
{

    printf("The command line has %d arguments :-\n", argc-1);

    for (int count = 1; count < argc; count++)
        printf("%d: %s\n", count, argv[count]);

    return 0;

}





/* Trivia

 * C compilers allow main() to have zero or two arguments (some implementations
   allow additional arguments, but that would be an extension of the standard).
 * With two arguments, the first argument is the number of strings in the
   command line, counted automatically by the compiler. By convention, but not
   necessarily, this parameter is called argc. The strings must be separated by
   spaces. Multi-word strings must be enclosed in double quotes.
 * The program stores the command line strings in memory and stores the
   addresses of their first elements in a 1-D array of pointers. The address of
   this array is stored in the second argument called argv by convention, but
   not necessarily.
 * When possible (some operating systems don't allow this), argv[0] is assigned
   the name of the program itself (for eg., ./a.out, ./hello, etc.)
 * argv[1] through argv[argc-1] are assigned the subsequent strings.
 * argv[argc] is assigned a null pointer (NULl).


 * C requires numeric forms for numeric operations, such as addition and
   comparison, but displaying numbers on the screen requires a string form
   because a screen displays characters. The printf() and sprintf() functions,
   through their %d and other specifiers, convert numeric forms to string forms,
   and scanf() can convert input strings into numeric forms.

 * The atoi() function, prototyped in stdlib.h, can be used to convert a string,
   among others, to an integer, but is not useful for error checking, as the C
   standard says that the behaviour if the string argument cannot be converted
   to an integer is undefined.
   [For eg., int a = atoi("1");
             int a = atoi(str);]
 * atoi() converts characters until it encounters something that is not part of
   an integer. For eg., int x = atoi("22 June"); assigns 22 to x.
   [Similar to scanf("%d", &x); assigning only 22 to x if 22 June is given as
    input and leaving ' ', 'J', 'u', 'n', 'e' and '\n' in the input buffer]
 * Functions similar to atoi() are atof() and atol(), for double and long
   conversions, respectively.

 * The strtol(), strtoul() and strtod() functions (for long, unsigned long and
   double conversions, respectively), also prototyped in stdlib.h, can be used
   only on strings and provide better methods for error checking.
   These functions can identify the first character in the string that is not
   part of a number. Also, strtol() and strtoul() allow the user to specify a
   number base corresponding to the string.
   strtol() and strtoul() use three arguments, whereas strtod() used only two.
   [For eg., char * end; long a = strtol(str, &end, 10);
             str gets converted to a long integer.
             The address of the pointer variable end is passed to the function,
             so that the function can set the value of end to the address of the
             character terminating the input number, which should be the null
             character if the string was converted completely.
             10 specifies the base (i.e. a decimal integer).]

 */
