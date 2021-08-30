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
 * The fputs() function, also prototyped in stdio.h, displays string and like
   printf(), it doesn't automatically append a newline at the end.
 * printf("%s", str), puts(str) and fputs(str, stdout) use the starting address
   of the string as their argument and keep printing till they reach the null
   character.
   [If str is the name of a character array, then it would decay to the starting
    address automatically]

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


 * To read a string into a program using an input function, space to store the
   string must be first set aside.
   For eg., char * name; scanf("%s", name); will probably not give any errors,
   but when a string is read, it might get written over something important,
   causing the program to crash. This is because name is an uninitialised
   pointer, pointing to a random memory location.

 * The gets() function reads an entire line upto the newline character (without
   skipping leading whitespaces) and discards the newline character after
   consuming it.
   scanf("%s", str), on the other hand, skips leading whitespaces, stops reading
   at the first whitespace and doesn't consume the trailing newline character
   (i.e. leaves the newline character in the input buffer).
   Both gets() and scanf("%s", str) add a null character at the end.
 * Using gets() is unsafe because it doesn't provide a way to check whether the
   input line actually fits into the space allotted for it, as opposed to
   scanf(), which provides a positiveInt modifier to limit the input.

 * Similar to the output functions printf(), puts() and fputs(), the input
   functions scanf(), gets() and fgets() also use the starting addresses as
   arguments.

 * One way to take an entire line as input using scanf(), other than taking
   individual characters as input using a loop, is by using
   scanf(" %positiveInt[^\n]", str);
   This skips leading whitespaces (due to the space) and leaves the trailing
   newline character in the input buffer.
   To consume and discard the trailing newline character, one can use
   scanf(" %9[^\n]%*c", str);
 * The reason why this is not preferred is because fgets() provides the same
   functionality and looks a lot cleaner.

 * The fgets() function is preferred over scanf() and gets() for string input.
 * fgets(str, positiveInt, stdin) :-
   (a) str is the starting address of the space set aside for the input (which
       is generally the name of a char array decayed to its starting address)
   (b) The first positiveInt-1 characters will be read from the input (leaving
       space for the null character which it adds automatically), or it will
       stop reading at the newline character if it comes before the limit is
       reached. It should be noted that the positiveInt in fgets() is one
       greater than the number of characters to be read, whereas the positiveInt
       modifier in scanf() is equal to the number of characters to be read.
   (c) The newline character, if read, is stored as part of the string, unlike
       gets() (which consumes and discards the newline character) and scanf()
       (which leaves the newline character in the input buffer).
   (d) Leading whitespaces aren't skipped, unlike scanf().
   (e) stdin indicates the file to be read, which is the standard input in this
       case.
 * fgets() returns a pointer-to-char.
   If all goes well, it returns the same address that was passed to it as the
   first argument.
   If fgets() encounters end of file or an error, then it returns a special
   pointer called the null pointer, which is guaranteed to not point to valid
   data so it can be used to indicate a special case. In code, a null pointer is
   represented by ((void *) 0), or more commonly by NULL.

 * There is an optional function for string input, i.e. the gets_s() function.


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
   array of pointers, as the pointers are pointing to const data (i.e. string
   literals).
 * sizeof subjects is 40 on this system, whereas sizeof days is 50.

 */
