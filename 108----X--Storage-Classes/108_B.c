#include <stdio.h>
#include "108.h"


static int total = 0;


void add(int i, int value)
{

    static int subtotal = 0;

    if (i > 0)
    {
        subtotal += i;
        total += i;
    }

    else
    {
        printf("Loop cycle: %d\n", count);
        printf("Sum of first %d numbers = %d\n", value, subtotal);
        printf("Total: %d\n\n", total);
        subtotal = 0;
    }

}
