// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>


struct book
{
    char title[40];
    char author[30];
    double price;
};


char * modified_fgets(char *, int);


int main(void)
{

    struct book library;

    printf("Enter the book title: "); modified_fgets(library.title, 40);
    printf("Enter the author: "); modified_fgets(library.author, 30);
    printf("Enter the price: Rs. "); scanf("%lf", &library.price);

    printf("\n\'%s\' by %s: Rs. %g\n",
           library.title, library.author, library.price);

    return 0;

}


char * modified_fgets(char * s, int n)
{

    char * returnValue = fgets(s, n, stdin);

    int i = 0;
    int c;

    if (returnValue)
    {
        while ((s[i] != '\n') && (s[i] != '\0'))
            i++;

        if (s[i] == '\n')
        {
            s[i] = '\0';
        }

        else // s[i] == '\0' (i.e. there are extra characters in the buffer).
        {
            while (((c = getchar()) != '\n') && (c != EOF))
                continue;
        }
    }

    return returnValue;

}





/* Trivia - 112.c

 * A structure can be thought of as a super-array, in which one element can be
   char, the next element double, and the next an int array.

 * A structure declaration is the master plan that describes how a structure is
   put together.
   For eg., struct book
            {
                char title[40];
                char author[30];
                double price;
            };
   This declaration describes a structure made up of two character arrays and
   one double variable.
   It does not create an actual object, but it describes what constitutes such
   an object.
   'book' is an optional tag that is a shorthand label that can be used to refer
   to this structure.

 * The members of a structure can be of any C data type, including other
   structures.

 * A structure declaration placed outside of all functions makes the tag
   accessible to every function, whereas a structure declaration placed inside
   a function makes the tag accessible only to that function.

 * The declaration struct book library; makes the compiler create a structure
   variable called library (using the book structure design) and allocate space
   for a char array of 40 elements, a char array of 30 elements and a double
   variable.
 * On some systems, the size of a structure may be greater than the sum of its
   parts. This is because a system's alignment requrirements for data may cause
   gaps. Fe eg., a system may have to place each member at an even address that
   is a multiple of four. Such structures might end up with unused space.

 * In declaring a structure variable, struct book (for eg.) plays the same role
   that int or double does in simpler declarations.
   For eg., struct book a, b, * p; declares a & b as structure variables based
   on the book structure design and p as a pointer to a structure based on the
   book structure design.

 * The process of declaring a structure and declaring a structure variable can
   be combined into one step, such as
   struct
   {
       char title[40];
       char author[30];
       double price;
   }
       library;
 * Declaring a structure variable alongwith declaring the structure doesn't
   mean that the structure tag cannot be used anymore in the program.
 * Omitting the tag would make the structure declaration unusable for other
   variables, like in this example.

 * A structure variable can be initialized as well.
   For eg., struct book library = { "C Primer Plus",
                                    "Stephen Prata",
                                    7000 };

 * The dot (.) operator is used to access the members of a structure.

 * Designated initializers for structures are also available, and are similar to
   designated initializers for arrays.
   For eg., struct name = { .last = "J", .first = "Kushagr", "Jaiswal" };
   ["Jaiswal" overrides "J"]
 * Compound literals can be used for structures as well, just like for arrays.
   For eg., (struct name) { "Kushagr", "Jaiswal" }
   As opposed to arrays, where arr = int[2] {1,2}; is not valid, assignment to
   structures is possible, such as name1 = (struct name) {"Kushagr", "Jaiswal"};
   [Similar rules to that of array compound literals apply here as well]

 * In C, one can use the same name for a tag and a variable in the same scope
   without causing errors.
   But, using the same name for two variables, or for two tags, in the same
   scope causes errors.

 * End of Trivia */
