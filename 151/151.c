// C17 Standard
// Include input validation in version B of this program.

#include <stdio.h>


char * modified_fgets(char *, int);


struct book
{
    char title[40];
    char author[30];
    double price;
};


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

 * A structure variable can be initialized as well.
   For eg., struct book library = { "C Primer Plus",
                                    "Stephen Prata",
                                    7000 };

 * The dot (.) operator is used to access the members of a structure.

 * Designated initializers for structures are also available, and are similar to
   designated initializers for arrays.

 */
