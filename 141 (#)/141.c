// C17 Standard

#include <stdio.h>
#include <stdlib.h>


int sum(int **, int, int);


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

    printf("The sum of all elements = %d\n", sum(arr, rows, cols));

    return 0;

}


int sum(int ** arr, int rows, int cols)
{

    int sum = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            sum += arr[i][j];

    free(arr);

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

 * A 2-D array can also be indirectly created as a 1-D array, as it is
   essentially stored contiguously in the memory.
   For eg., int arr[][3] = { {1,2,3}, {4,5,6} }; int (* p)[3] = arr;
            int * q = arr[0];
            Here, p[1][2] is equivalent to q[5], and so on.
 * Similarly, a 1-D malloced block can also be used to simulate a 2-D array.

 */
