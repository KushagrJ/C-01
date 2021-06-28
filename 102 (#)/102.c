// C17 Standard

#include <stdio.h>


int sum(const int (*)[3], int);
// or int sum(const int [][3], int);           - Any non-negative integer can be
// or int sum(const int (* arr)[3], int rows);   written inside the first []. It
// or int sum(const int arr[][3], int rows);     will get ignored anyway.


int main(void)
{

    int arr[][3] = { {1,2,3},
                     {4,5,6},
                     {7,8,9},
                     {1,2,3} };

    int rows = (sizeof arr) / (sizeof arr[0]);

    printf("The sum of all elements = %d\n", sum(arr, rows));

    return 0;

}


int sum(const int (* arr)[3], int rows)
// or int sum(const int arr[][3], int rows)
{

    int sum = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < 3; j++)
            sum += arr[i][j];

    return sum;

}





/* Trivia

   int arr[][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
   Here, (a) arr/&arr[0], arr[0]/&arr[0][0] and &arr represent the same address.
         (b) arr (in most cases) and &arr[0] have the data type int (*)[3],
             arr[0] (in most cases) and &arr[0][0] have the data type int *,
             and &arr has the data type int (*)[2][3].

   Internal representation of this 2-D array:-
   +---+---+---+---+---+---+---+---+---+
   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
   +---+---+---+---+---+---+---+---+---+
   |   |       |           |           |
   |   |       |           |           |
   |   |       &arr[1]     &arr[2]     &arr[3]
   |   |       |           |           |
   |   |       &arr[1][0]  &arr[2][0]  &arr[3][0]
   |   |                               |
   |   &arr[0][1]                      (&arr)[1]
   |
   &arr
   |
   &arr[0]
   |
   &arr[0][0]
   |
   (&arr)[0]

   Of course, arr[3][0] is out of bounds, but its address can be used like
   &arr[3][0] by the logic of pointers discussed below.
   As always, dealing with the values at invalid indexes is undefined behaviour.
   Thus, the values at arr[3][0], arr[3][1], arr[3][2], arr[4][0], etc.
   shouldn't be accessed.
   [It is only guaranteed that the address one past the end element of an array
    is valid.
    C doesn't guarantee the validity of the addresses of arr[3][1], arr[3][2],
    arr[4][0], etc.]

   Adding 1 to a pointer or address yields a value 1 larger than the size of
   the referred-to object. In this respect as well, arr and arr[0] differ, as
   arr refers to an object 3 ints in size, and arr[0] refers to an object 1
   int in size. Therefore, arr + 1 has a different value from arr[0] + 1.

   Also, *(arr[0]) represents the value stored in arr[0][0], i.e. an int.
   Similarly, **arr also represents the value stored in arr[0][0], as *arr
   reduces to arr[0].
   [Thus, for 1-D arrays, arr decays to a pointer and for 2-D arrays, arr decays
    to a 'pointer to a pointer']

   The pointer notation equivalent of arr[2][1] is *(*(arr+2)+1).
   As always, both the notations work even if arr is a pointer.
   Similarly for higher dimensions.

   int (* p)[3]; declares p to be a pointer to an array of 3 ints.
   p can now point to a 2-D array having 3 columns and any number of rows,
   for eg. by using the statement p = arr;.
   [This is similar to int * p declaring p to be a pointer to an integer that
    can point to a 1-D array having any number of elements]

   In function prototypes and headers (where [] can be used to declare
   pointers), to declare a pointer corresponding to an N-dimensional array,
   bounds for all dimensions except the first must be provided.
   If provided, the non-negative integer inside the first pair of brackets will
   get ignored.
   For eg., int (* p)[10][20][30] is the same as int p[][10][20][30] in function
   prototypes and headers. p can now point to a 4-D array.

 */
