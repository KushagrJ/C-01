// C17 Standard

#include <stdio.h>


int sum(const int *, int);


int main(void)
{

    printf("The sum is %d\n", sum((int []) {0,1,2,3,4,5,6,7,8,9}, 10));

    return 0;

}


int sum(const int * integers, int size)
{

    int sum = 0;

    for (int i = 0; i < size; i++)
        sum += integers[i];

    return sum;

}





/* Trivia

 * Literals are constants that aren't symbolic. For eg., 5 is a type int
   literal, 81.3 is a type double literal, 'Y' is a type char literal and
   "element" is a string literal.

 * The compound literal that creates a nameless array equivalent to
   int arr[2] = {10,20}; is (int [2]) {10,20} or (int []) {10,20}
 * Because these compound literals are nameless, therefore they can't be created
   in one statement and then used later. Instead, they have to be used somehow
   at the time of creation.
 * One way to use compound literals is by using a pointer to keep track of the
   location.
   For eg., int * p = (int []) {10,20};
   Like normal arrays, the compound literal (int []) {10,20} also translates to
   the address of the first element, so it can be assigned to a pointer-to-int.
   Now, *p would be 10, p[1] would be 20, and so on.
   Also, the values can be changed like *(p+1) = 5;, and so on.
   [Similar logic for string literals]
 * Another way to use compound literals could be to pass them as arguments to
   functions with matching parameters, just like normal literals.
   For eg., int sum(const int * arr, int size);
            ...
            int sum = sum((int []) {1,2,3,4,5,6}, 6);
   Here also, the address of the first element of the array gets passed.

 * Compound literals used within a block have block scope and automatic storage
   duration (discussed later).
   This means that the existence of the compound literal is not guaranteed once
   the program's execution leaves the block in which the compound literal is
   defined.
 * Compound literals occurring outside of any function have static storage
   duration (discussed later).

 */
