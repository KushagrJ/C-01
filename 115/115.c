// C17 Standard

#include <stdio.h>


struct funds
{
    char bank1[20];
    double bank1Fund;
    char bank2[20];
    double bank2Fund;
};


void print_bank_names(struct funds);
double sum(const struct funds *);


int main(void)
{

    struct funds stephen = { "Garlic-Melon Bank",
                             3526.87,
                             "Pizza-Pasta Bank",
                             1459.35 };

    print_bank_names(stephen);
    printf("Total: Rs. %g\n", sum(&stephen));

    return 0;

}


void print_bank_names(struct funds stephen)
{
    printf("Bank 1: %s\n", stephen.bank1);
    printf("Bank 2: %s\n", stephen.bank2);
}


double sum(const struct funds * pointerToStephen)
{
    return (pointerToStephen->bank1Fund) + (*pointerToStephen).bank2Fund;
}





/* Trivia

 * Structures can be passed either by value or by reference to functions.
 * Similar to others, passing a structure by value makes the receiving function
   get a copy of the original structure, but passing a structure by reference
   makes the receiving function get access to the original structure.

 */
