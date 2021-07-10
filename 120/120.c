// C17 Standard

#include <stdio.h>
#include <string.h>


int main(void)
{

    return 0;

}





/* Trivia

 * The strcat() function, prototyped in string.h, takes the addresses of two
   strings as arguments. A copy of the second string is attached to the end of
   the first string, and this combined version becomes the new first string.
   strcat() returns the address of the first string.
   [For eg., char * str3 = strcat(str1, str2); - str3 and str1 point to the same
    string]
 * The first string needs to be modifiable (a non-const char array), whereas
   the second string can be a string literal or a char array.
 * The first string's array needs to be large enough to accomodate the
   concatenation.
 * Basically, the first string's null character is removed and the second string
   (including the null character) is attached to the end.

 * The strncat() function, also prototyped in string.h, works similar to the
   strcat() function, but also provides a way to prevent overflows if the first
   string's array is not large enough for the concatenation.
   [For eg., char * str3 = strncat(str1, str2, positiveInt);]
 * positiveInt specifies the maximum number of characters to add to str1 from
   str2 (excluding str2's null character).

 * The strcmp() function, also prototyped in string.h, is used to compare two
   strings.
 * str1 == str2 or str1 != str2 doesn't work because these are addresses, and
   not the entire strings.
 * strcmp() takes the addresses of two strings as its arguments. It returns 0 if
   the strings are same and a non-zero value otherwise.
   [For eg., int a = strcmp(str1, str2);]
 * strcmp() returns a negative value if the first string comes before the second
   string sequentially (generally ASCII), returns 0 if they are same and returns
   a positive number if the first string comes after the second string
   sequentially.
   The exact numerical values are left open to the implementation.
   In general, strcmp() moves along until it finds the first pair of disagreeing
   characters. It then returns the corresponding code.
 * Equal strings need not belong to different arrays of same size in order for
   strcmp() to return 0, as it stops comparing when a null character in either
   strings is reached.
   [For eg., char str1[10] = "Kushagr"; char str2[20] = "Kushagr";
             printf("%d\n", strcmp(str1, str2); prints 0]

 * The strncmp() function, also prototyped in string.h, works similar to the
   strcmp() function, but also provides a way to limit the number of characters
   to be checked.
   [For eg., int a = strncmp(str1, str2, positiveInt); checks whether the
    strings are same upto the first positiveInt characters, or before a null
    character in either strings is reached, whichever is earlier]

 */
