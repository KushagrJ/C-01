// C17 Standard

#include <stdio.h>


int main(void)
{

    // A 1-D array of pointers to const char.
    const char * subjects[] = { "Programming",
                                "Mathematics",
                                "Algorithms",
                                "Database Management",
                                "Networks" };

    // A 2-D array of chars (or an array of strings).
    char days[][10] = { "Monday",
                        "Tuesday",
                        "Wednesday",
                        "Thursday",
                        "Friday" };

    printf("%-20s  %s\n\n", "Subjects", "Days");

    for (int i = 0; i < 5; i++)
        printf("%-20s  %s\n", subjects[i], days[i]);

    return 0;

}





/* Trivia

 * The puts() function, prototyped in stdio.h, displays strings, and unlike
   printf(), it automatically appends a newline at the end.

 * The principal ways to define a string are by using string constants (i.e.
   string literals), char arrays and char pointers.

 * A string literal is anything enclosed in double quotation marks. The enclosed
   characters, plus a terminating null character automatically provided by the
   compiler, are stored in the memory as a character string.
 * C concatenates string literals if they are separated by nothing or
   whitespace.
   For eg., char str[15] = "C"  " Pro""gramm"
                           "ing";
            is the same as char str[15] = "C Programming";
 * String literals are placed in the static storage class (discussed later),
   which means that if a string literal is used in a function, the string is
   stored just once and lasts for the duration of the program, even if the
   function is called several times.
   [Actually, the compiler has the freedom to store a literal that's used more
    than once in one or more locations, but generally, a literal is stored just
    once and is used multiple times from that same address]
 * Just like other arrays, the entire quoted phrase acts as a pointer to the
   first character.
   For eg., printf("%p, %c\n", "Kushagr", *"Jaiswal"); printed 0x56203e0c1004, J
            printf("%c\n", *("Kushagr"+1)); prints u
 * char str[] = "Kushagr J"; is similar to (but not the same as)
   char str[] = {'K','u','s','h','a','g','r',' ','J','\0'};
   [Without the null character, str would be a character array, and not a
    string]
   [Like other arrays, str[2] = 'n', etc. can be done with strings as well]
 * When a string is taken as input, then the extra elements of the char array
   are garbage (in general), but when a char array is initialized, then the
   extra elements are initialized to 0, which means '\0' for a char array.
 * Even though char str[] = "Kushagr"; and char * str = "Kushagr"; are very
   similar, there is a major difference between the two.
   The array form causes a char array of 8 elements to be allocated in the
   computer memory. The quoted string is said to be in static memory, i.e. when
   the program is loaded into memory, the quoted string is also loaded into
   memory. But, the memory for an array is allocated only after the program
   begins running. At that time, the quoted string is copied into the array.
   Thus, at this time, there are two copies of the string. One is the string
   literal in static memory, and one is the string stored in the array. Also,
   while operations such as str+1 can be used with the array form, the location
   of the array can't be changed, i.e. operations like str = <new address>,
   str++, etc. can't be used (same as with other arrays, since the decayed
   arrays aren't lvalues).
   The pointer form also causes 8 elements in static memory to be set aside for
   the string, but it also sets aside one more storage location for the pointer
   variable str and stores the address of the string in str. This variable str
   initially points to the first character of the string, but its value can be
   changed, like str = <new address>, str++, etc. Unlike the array form, no two
   copies of the string are created here.
 * A string literal is considered to be const data. So, const char * str should
   be used for string literals, such as const char * str = "Kushagr";
   [char * str can be used, but a warning would be issued on most compilers,
    and any attempt to modify const data using a non-const identifier results in
    undefined behaviour - same as before]
   With the array form, unless the array itself is declared as a constant array,
   the string can be modified, as it is esentially a copy of the original string
   literal.


 * In this program, in some ways, subjects and days are much alike. Each
   represents five strings. When used with one index, as in subjects[0] and
   days[1], the result is a single string.
   And, just as subjects[1][2] is 't' (the third character of the second string
   represented by subjects), days[1][2] is 'e' (the third character of the
   second string represented by days). Both are initialized in the same fashion.
   [Again, both the array and the pointer notations can be used here as well]
 * But, since subjects is not a 2-D array of chars, and is rather just a 1-D
   array of pointer variables, the string literals of subjects need not be
   stored contiguously in the memory.
   The elements of subjects are simply the addresses of the first elements of
   the string literals, and not the entire string literals (or rather, the
   copies of the string literals).
   Furthermore, the allocation of memory in the array days is inefficient, as
   each element of days has to be the same size, and that size has to be at
   least large enough to hold the longest string. Again, for a 2-D array of
   char, copies of strings are made, whereas for an array of pointers to
   char, no such copies are made.
 * Thus, if an array is to be used to represent a bunch of strings, then an
   array of pointers is more efficient than an array of arrays of char.
   But, if the strings need to be altered, then this is not possible with an
   array of pointers, as the pointers are pointing to constant data (i.e. string
   literals).
 * sizeof subjects is 40 on this system, whereas sizeof days is 50.

 */
