// C17 Standard
// Include input validation in version B of this program.

#include <stdio.h>
#include <string.h>


struct name
{
    char first[20];
    char last[20];
    unsigned numberOfLetters;
};


struct name * get_name(struct name *);
struct name calculate_number_of_letters(struct name *);
void show_info(struct name);
char * modified_fgets(char *, int);


int main(void)
{

    struct name guy1;

    struct name * pointerToSomeGuy = get_name(&guy1);

    struct name guy2 = calculate_number_of_letters(pointerToSomeGuy);

    show_info(guy2);

    return 0;

}


struct name * get_name(struct name * pointerToSomeGuy)
{

    printf("Enter your first name: ");
    modified_fgets(pointerToSomeGuy->first, 20);

    printf("Enter your last name: ");
    modified_fgets(pointerToSomeGuy->last, 20);

    return pointerToSomeGuy;

}


struct name calculate_number_of_letters(struct name * p)
{

    p->numberOfLetters = (unsigned) (strlen(p->first) + strlen(p->last));

    return *p;

}


void show_info(struct name guy)
{
    printf("\nYour name has %u letters\n", guy.numberOfLetters);
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

 * Similar to variables, one structure can be assigned to another structure of
   the same type, unlike arrays, since a structure name doesn't decay to its
   address.
   This works even if a member happens to be an array.
   [Thus, one way to pass an array to a function by value is to create a
    structure containing that array and then passing that structure by value]
 * Also, one structure can be inintialized to another of the same type.
   For eg., struct names one = { "Kushagr", "Jaiswal" };
            struct names two = one;
   [Similar to int y = 1; int x = y;]
   [This is similar to what happens when an object is passed to a function by
    value. The parameter is initialized to the passed argument.]

 */
