// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdarg.h>


void add_and_multiply(int *, long long *, int, ...);


int main(void)
{

    int arr[5];

    printf("Enter 5 integers: ");
    for (int i = 0; i < 5; i++)
        scanf("%d", &arr[i]);

    int sum = 0;
    long long product = 1;

    add_and_multiply(&sum, &product, 5, arr[0], arr[1], arr[2], arr[3], arr[4]);

    printf("Their sum is %d and their product is %lld\n", sum, product);

    return 0;

}


void add_and_multiply(int * ptr_sum, long long * ptr_product, int n, ...)
{

    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++)
    {
        int temp = va_arg(ap, int);
        *ptr_sum += temp;
        *ptr_product *= (long long) temp;
    }

    va_end(ap);

}





/* Trivia - 121.c

 * The stdarg.h header file provides the capability for creating functions that
   accept a variable number of arguments.

 * The prototype and header for such a function should have a parameter list
   with at least one parameter followed by an ellipsis. The ellipsis should be
   placed at the end.

 * The va_list type represents an object used to hold the parameters
   corresponding to the ellipsis part of the parameter list.
 * The va_start() macro copies the argument list to the va_list variable. It
   takes two arguments, namely the va_list variable and the number of arguments
   in the variable-argument list.

 * The va_arg() macro is used to gain access to the contents of the argument
   list. It takes two arguments, namely the va_list variable and the data type
   of the object to be retrieved.
 * The first time va_arg() is called, it returns the first item in the list. The
   second time it's called, it returns the second item in the list. And so on.
 * The data types should match properly, as the implicit data conversion doesn't
   work here.

 * Finally, the va_end() macro is used to clean up, such as freeing memory
   dynamically allocated to hold the arguments. It takes one argument, namely
   the va_list variable.

 * Since va_arg() doesn't allow the user to access the previous items, the macro
   va_copy() can be used to create a copy of the parameter list to be used
   later. It takes two arguments, namely the target va_list variable and the
   source va_list variable.
   For eg, va_copy(ap_copy, ap);

 * End of Trivia */
