// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdlib.h>


struct marksOfTheStudent
{
    double mathematics;
    double programming;
    double algorithms;
    double average;
};

struct student
{
    char name[20];
    struct marksOfTheStudent marks;
};


void sort_pointers_to_structures(const struct student **);


int main(void)
{

    printf("Enter the details of 5 students :-\n\n");
    printf("%-19s %-19s %-19s %-19s\n\n", "Name", "Mathematics",
                                          "Programming", "Algorithms");

    struct student * students =
        (struct student *) malloc(5 * sizeof(struct student));

    for (int i = 0; i < 5; i++)
    {
        fgets(students[i].name, 20, stdin);
        scanf("%lf", &students[i].marks.mathematics);
        scanf("%lf", &students[i].marks.programming);
        scanf("%lf", &students[i].marks.algorithms);
        getchar();
    }

    for (int i = 0; i < 5; i++)
        students[i].marks.average =
            (students[i].marks.mathematics + students[i].marks.programming +
             students[i].marks.algorithms) / 3;

    const struct student * p[5];
    for (int i = 0; i < 5; i++)
        p[i] = &students[i];

    sort_pointers_to_structures(p);

    printf("\n\nAfter sorting according to average marks :-\n\n");
    printf("%-19s %-19s %-19s %-19s\n\n", "Name", "Mathematics",
                                          "Programming", "Algorithms");

    for (int i = 0; i < 5; i++)
        printf("%-19s %-19g %-19g %-19g\n", p[i]->name,
                                            p[i]->marks.mathematics,
                                            p[i]->marks.programming,
                                            p[i]->marks.algorithms);

    free(students);

    return 0;

}


void sort_pointers_to_structures(const struct student ** p)
{

    const struct student * temp;

    for (int i = 1; i < 5; i++)
        for (int j = 0; j < 5-i; j++)
            if (p[j]->marks.average < p[j+1]->marks.average)
                temp = p[j], p[j] = p[j+1], p[j+1] = temp;

}





/* Trivia - 117.c

 * Pointers to structures are generally used as function arguments for reasons
   of efficiency, using const when needed to protect data from unintended
   changes.
   Passing structures by value is most often done for structures that are small
   to begin with, or by passing only the required members of large structures
   individually.


 * A union is a type that can be used to store different data types in the same
   memory space (but not simultaneously).
 * The compiler allots enough space so that it can hold the largest of the
   described possibilities.

 * Unions are set up in much the same way as structures, i.e. declarations,
   initializations, accessing, anonymous unions, etc. are similar to structures.
   For eg., union data
            {
                int i;
                double d;
                char c;
            };
   A structure with a similar declaration would be able to hold an int value
   'and' a double value 'and' a char value. This union, however, can hold an int
   value 'or' a double value 'or' a char value.

 * Union initializations :-
   union data first;
   first.c = 'R';
   union data second = first; // initialize one union to another
   union data third = {88}; // initialize i member of union
   union data fourth = {.d = 118.2}; // designated initializer

 * It is the programmer's responsibility to write the program so that it keeps
   track of the data type currently being stored in a union.
 * Things like union data { char c; int i; }; union data first; first.c = 'K';
   printf("%d\n", first.i); don't give warnings or errors, but should always be
   avoided, unless its a special case.


 * The enumerated type can be used to declare symbolic names to represent
   integer constants.
 * For eg., enum spectrum {red, orange, yellow, green, blue, indigo, violet};
   makes red a symbolic constant for 0, orange a symbolic constant for 1,
   yellow a symbolic constant for 2, and so on.
   [These symbolic constants can be used as sizes in non-VLA declarations,
    labels in a switch statement, etc. Thus they aren't const variables, but
    are symbolic constants, similar to #define constants.]
 * Like structures and unions, enum spectrum now becomes the name of a type.
   Now, for a statement like enum spectrum colour;, colour becomes an
   enumerated variable (which is basically of an integer type) which can take
   the values 0, 1, 2, 3, 4, 5 and 6, or more specifically, red, orange,
   yellow, green, blue, indigo and violet.
   colour can also take values out of the given range, but it isn't always
   guaranteed to work, as the actual integer type used varies.
   Thus, enum spectrum colour = red; // OK
         enum spectrum colour = 4; // OK
         enum spectrum colour = purple; // Error
         enum spectrum colour = 7; // OK (mostly)
         enum spectrum colour = 123456789987654321; // Overflow (mostly)
         int a = red; // OK
         unsigned b = orange; // OK
         long c = yellow; // OK
         char d = green; // OK
   [The compiler is free to choose the integer type to represent an enumerated
    type. For eg., here the compiler could choose an unsinged char to represent
    the variable colour in this case.]

 * One can choose the integer values to assign to the enumerators as well.
   For eg., (a) enum levels {low = 100, medium = 500, high = 2000}; makes low,
                medium and high symbolic constants for 100, 500 and 2000,
                respectively.
            (b) enum furniture {chair, table = 10, bed}; makes chair, table and
                bed symbolic constants for 0, 10 and 11, respectively.


 * typedef enables the creation of custom names for a type.
 * Unlike #define, typedef is limited to giving symbolic names to types only.
   Also, the interpretation is performed by the compiler, instead of the
   preprocessor - similar to enum symbolic constants.
 * For eg., typedef unsigned char BYTE;
            BYTE x = 'K';
   The scope (i.e. the usage of BYTE instead of unsigned char) depends on the
   location of the typedef statement. If it is inside a function, then the scope
   is local, but if it is outside any function, then the scope is global.
 * The types size_t, time_t, etc. are actually typedef types, as the actual
   type depends upon the implementation.
   Thus, on one system, size_t can be unsigned long, but on another, it can be
   unsigned int.


 * A pointer to a function holds the address marking the start of the function
   code.
   Unlike objects, the address of a function doesn't refer to data values, and
   rather refers to executable code within memory.
 * Typically, a function pointer is used as an argument to another function,
   telling the second function which function to use.
 * For eg., for the function void to_upper(char *);, the pointer can be declared
   as void (* p)(char *);
   One way to understand this pointer declaration is that to_upper is replaced
   by (* p).
 * In the contexts of assigning the address of a function to a pointer and
   passing the address of a function to another function, the function name can
   be treated as its address.
   For eg., p = to_upper; // OK
            p = to_upper(); // Error
            my_printf(to_upper); // OK, passes address of to_upper()
            my_printf(to_upper(str)); // OK, passes return value of to_upper()
 * Surprisingly, to call a function using a pointer, one can use p() as well as
   (* p)();

 * End of Trivia */
