// C17 Standard
// Include input validation in version B of this program.

#include <stdio.h>
#include <string.h>


// <type> ** / <type> *[] is for a 1-D array of pointers / pointers-to-pointers.
void sort_pointers_to_strings(char **, int);
// or void sort_strings(char *[], int);

char * modified_fgets(char *, int);


int main(void)
{

    char inputArray[10][100];
    char * pointersToStrings[10];

    printf("Enter upto 10 lines to be sorted :-\n");
    printf("(To stop, press ENTER on a newline)\n\n");

    int count = 0;
    while ((count < 10) &&
           (modified_fgets(inputArray[count], 100) != NULL) &&
           (inputArray[count][0] != '\0'))
    {
        pointersToStrings[count] = inputArray[count];
        count++;
    }

    sort_pointers_to_strings(pointersToStrings, count);

    puts("\nHere's the sorted list :-\n");
    for (int i = 0; i < count; i++)
        puts(pointersToStrings[i]) ;

    return 0;

}


void sort_pointers_to_strings(char ** strings, int n)
{

    // Similar to bubble sort.

    char * temp;

    for (int i = 1; i < n; i++)
        for (int j = 0; j < n-1; j++)
            if (strcmp(strings[j], strings[j+1]) > 0)
            {
                temp = strings[j];
                strings[j] = strings[j+1];
                strings[j+1] = temp;
            }

}


char * modified_fgets(char * s, int n)
{

    char * returnValue;
    int i = 0;

    returnValue = fgets(s, n, stdin);

    if (returnValue)
    {
        while ((s[i] != '\n') && (s[i] != '\0'))
            i++;
        if (s[i] == '\n')
            s[i] = '\0';
        else // s[i] == '\0' (i.e. there are extra characters in the buffer).
            while (getchar() != '\n')
                continue;
    }

    return returnValue;

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
 * Basically, the second string (including its null character) is attached at
   the end of the first string, starting with the first string's null character
   (i.e. overwriting the first string's null character).

 * The strncat() function, also prototyped in string.h, works similar to the
   strcat() function, but also provides a way to prevent overflows if the first
   string's array is not large enough for the concatenation.
   [For eg., char * str3 = strncat(str1, str2, positiveInt); - str3 and str1
    point to the same string]
 * positiveInt specifies the maximum number of characters to add to str1 from
   str2 (excluding str2's null character).
 * The null character of str2 is not copied (as opposed to strcat()), and a null
   character is appended to the result.

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

 * The strcpy() function, also prototyped in string.h, is used to copy strings.
 * str1 = str2 doesn't work because these are addresses, and not the entire
   strings.
 * strcpy() takes the addresses of two strings as its arguments and copies the
   second string into the first string.
   strcpy() returns the address of the first string.
   [For eg., char * str3 = strcpy(str1, str2); - str3 and str1 point to the same
    string]
 * The first string needs to be modifiable (a non-const char array), whereas
   the second string can be a string literal or a char array.
 * The first string's array needs to be large enough to accomodate the copying.
 * Also, the first string need not point to the beginning of an array.
   [For eg., char str[20] = "Kushagr Jaiswal";
             char * p = strcpy(str+4, " Jaiswal");
             makes str equal to "Kush Jaiswal" and p points to the space
             character after Kush.
    Basically, the entire string from the second argument is copied to the first
    one starting with the given address, including the null character from the
    second string. Thus, after copying, str looks like
    {'K','u','s','h',' ','J','a','i','s','w','a','l','\0','a','l','\0'}.]
   [Similar logic can be applied to strcat(), strncat() and strncpy()]

 * The strncpy() function, also prototyped in string.h, works similar to the
   strcpy() function, but also provides a way to prevent overflows if the first
   string's array is not large enough for the copying.
   [For eg., char * str3 = strncpy(str1, str2, positiveInt); - str3 and str1
    point to the same string]
 * positiveInt specifies the maximum number of characters to copy to str1 from
   str2 (including str2's null character).
   [In strncat(), the maximum number of characters excludes str2's null
    character, and in strncpy(), it includes str2's null character]

 * The strchr() function, also prototyped in string.h, returns a pointer to the
   first location in the string s that holds the character c. The terminating
   null character is part of the string, so it can be searched for. The function
   returns a null pointer if the character is not found.
   [For eg., char * p = strchr(s, c);]

 * The strrchr() function, also prototyped in string.h, returns a pointer to the
   last location in the string s that holds the character c. The terminating
   null character is part of the string, so it can be searched for. The function
   returns a null pointer if the character is not found.
   [For eg., char * p = strrchr(s, c);]

 * The strpbrk() function, also prototyped in string.h, returns a pointer to the
   first location in the string s1 that holds any character found in the string
   s2. The function returns a null pointer if no character is found.
   [For eg., char * p = strpbrk(s1, s2);]

 * The strstr() function, also prototyped in string.h, returns a pointer to the
   first occurrence of the string s2 in the string s1. The function returns a
   null pointer if the string is not found.
   [For eg., char * p = strstr(s1, s2);]

 * The sprintf() function, prototyped in stdio.h, works like printf(), but
   writes to a string instead of writing to a display.
   Its first argument is the address of the target string. The remaining
   arguments are the same as for printf().
   [For eg., char str[100];
             sprintf(str, "The sum of %d and %d is %d", 1+2, 3+4, 1+2+3+4);
             puts(str);
             prints The sum of 3 and 7 is 10]

 */
