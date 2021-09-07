// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdlib.h>


char * modified_fgets(char *, int);


struct book
{
    char title[40];
    char author[50];
    double price;
};


int main(void)
{

    // struct book library[size]; may cause stack overflow for a large size.
    struct book * library = (struct book *) malloc(3 * sizeof (struct book));
    if (library == NULL)
        exit(EXIT_FAILURE);
    struct book library[3];

    for (int i = 0; i < 3; i++)
    {
        printf("Book no. %d :-\n", i+1);
        printf("Enter the book title: "); modified_fgets(library[i].title, 40);
        printf("Enter the author: "); modified_fgets(library[i].author, 50);
        printf("Enter the price: Rs. "); scanf("%lf", &library[i].price);
        while (getchar() != '\n')
            continue;
        printf("\n");
    }

    struct book * p = &library[0];
    // or simply struct book * p = library, since library is a 1-D array and
    // will decay to &library[0].

    printf("\nHere are the books you entered :-\n\n");
    for (int i = 0; i < 3; i++, p++)
        printf("\'%s\' by %s: Rs. %g\n",
               library[i].title, (*(library + i)).author, p->price);

    free(library);

    return 0;

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

 * struct book library[size]; (and using the array-pointer similarities,
   struct book * library = (struct book *) malloc(size * sizeof (struct book));)
   can be used to create an array of structures.
   library[0], library[1], library[2], etc. can be thought of as structure
   variables (similar to an array of pointers).

 * In this program, library[0].title, (*(library + 0)).title and p->title are
   equivalent (provided p initially points to library[0]).
   These notations are equivalent even if library is created as an array,
   instead of using malloc().

 */
