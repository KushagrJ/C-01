// C17 Standard

#include <stdio.h>
#include <stdlib.h>


int sum(const int *, int);


int main(void)
{

    int * integers = (int *) malloc(10 * sizeof (int));
    if (integers == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < 10; i++)
        integers[i] = i;

    printf("The sum is %d\n", sum(integers, 10));

    free(integers);

    return 0;

}


int sum(const int * integers, int size)
{

    int sum = 0;

    for (int i = 0; i < size; i++)
        sum += integers[i];

    return sum;

}





/* Trivia - 110.c

 * The allocated storage duration allows the usage of library functions to
   allocate and manage memory.

 * The malloc() function, prototyped in stdlib.h, takes one argument, i.e. the
   number of bytes of free memory wanted, and finds a suitable block of free
   memory.
 * It returns the address of the first byte of the free block, in the form of
   a pointer-to-void, which is a generic pointer.
   The type cast should be done to the required type manually for clarity.
 * If malloc() fails to find the required space, then it returns the null
   pointer.
 * Also, the exit() function is called to terminate the program if memory
   allocation fails. The arguments of exit() should be either EXIT_FAILURE or
   EXIT_SUCCESS.
   [A function similar to malloc() is calloc(), which takes two arguments. The
    first argument is the number of memory cells needed, and the second argument
    is the size of each cell in bytes.
    Also, calloc() initializes all elements to zero.]

 * 3 ways that can be used to create arrays are :-
   (a) Declaring an array using a constant positive integer expression.
   (b) Declaring a VLA using a variable expression.
   (c) Declaring a pointer using malloc().
 * (b) and (c) are examples of dynamic arrays.
 * (c) is more flexible than (b).

 * The free() function, also protoyped in stdlib.h, takes as its argument an
   address returned earlier by malloc() and frees up the memory that had been
   allocated.
 * Generally, each use of malloc() should be balanced with a use of free().
 * The same memory block can be created in one function and freed in another
   function.

 * Thus, the allocated storage duration is from when malloc() is called to
   allocate memory until free() is called to free up the memory so that it can
   be reused.

 * The amount of memory needed for static objects is known at compile time, and
   the data stored in this section is available as long as the program runs.
 * The memory management of automatic objects is typically handled as a stack.
   For eg., new variables are added sequentially in memory as they are created
   and then are removed in the opposite order as they pass away.
 * Dynamically allocated memory is controlled by the programmer, and not by a
   set of rigid rules. This is why the section of memory used for dynamic
   memory allocation (often called a heap) can end up fragmented, i.e. unused
   chunks could be interspersed among active blocks of memory. Also, using
   dynamic memory tends to be a slower process than using a stack memory.
   [A VLA is different from a malloced block in many ways, such as a VLA is
    generally stored on the stack (since a VLA has automatic storage duration),
    whereas a malloced block is always taken from the heap. Also, a VLA has
    fixed size once allocated, whereas a malloced block can be resized.]

 * End of Trivia */
