// C17 Standard

#include <stdio.h>
#include <stdlib.h>


int sum(const int * const *, int, int);


int main(void)
{

    int rows = 2;
    int cols = 3;

    int ** arr = (int **) malloc(rows * sizeof (int *));
    if (arr == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < rows; i++)
    {
        arr[i] = (int *) malloc(cols * sizeof (int));
        if (arr[i] == NULL)
            exit(EXIT_FAILURE);
    }

    int num = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++, num++)
            arr[i][j] = num;

    printf("The sum of all elements = %d\n",
           sum((const int * const *) arr, rows, cols));

    for (int i = 0; i < rows; i++)
        free(arr[i]);
    free(arr);

    return 0;

}


int sum(const int * const * arr, int rows, int cols)
{

    int sum = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            sum += arr[i][j];

    return sum;

}





/* Trivia

 * One way to dynamically allocate a 2-D array is to allocate a malloced block
   of pointers to the starting addresses of the rows.
   Thus, this isn't exactly a 2-D array.
 * This method doesn't ensure contiguous rows (similar to how string literals
   need not be stored contiguously for a 1-D array of pointers to those
   strings).
   [Rows can be made contiguous by using explicit pointer arithmetic, but then
    a later reallocation of individual rows will become more difficult]

 * A 2-D array can also be indirectly used as a 1-D array, as it is essentially
   stored contiguously in the memory.
   For eg., int arr[][3] = { {1,2,3}, {4,5,6} }; int (* p)[3] = arr;
            int * q = arr[0];
            Here, p[1][2] is equivalent to q[5], and so on.
   [Similar logic for malloced blocks]


 * (a) For a non-const n-dimensional array of values of a primitive data type
       (char, int, float, double, etc.), passing the array name to a function
       that expects a const qualified pointer is fine, as the implicit
       conversion in this case is safe and the compiler should not complain
       about incompatible pointer type conversion.
       The reason the implicit conversion is safe in this case is because when
       an array is created, the values are guaranteed to be stored contiguously
       in the memory, no matter the dimension of the array.

 * (b) Now, for a malloced block of values of a primitive data type, a similar
       logic applies and the starting address of the block can be passed to a
       function that expects a const qualified pointer.

 * (c) But, for a malloced block of pointers that point to different malloced
       blocks of values a primitive data type (i.e. for a dynamically allocated
       equivalent of a 2-D array of values of a primitive data type, such as in
       this program), the implicit conversion should be considered unsafe by the
       compiler.
       The reason is because these pointers point to 'rows' that may be stored
       in different memory locations, unlike a 2-D array, where every 'row'
       begins immediately after the previous one ends.
       Also, these pointers may be made to point somewhere else (for eg., two
       rows can be swapped with each other), something that is impossible in a
       2-D array.
       Thus, in this case, in order to be safe, in the function declaration,
       every pointer to 'rows' should be declared as a constant pointer, in
       addition to making these pointers point to constant data.
       So, for eg., int sum(const int ** arr, ...) is not enough, as this only
       ensures that the values will not be changed by this function.
       On the other hand, int sum(const int * const * arr, ...) also ensures
       that the individual pointers will not be made to point anywhere else.
       Finally, in the function call, explicitly casting the pointer is
       necessary, as opposed to cases (a) and (b) above.

 */
