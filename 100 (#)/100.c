// C17 Standard

#include <stdio.h>


int sum(int * integers, int size);
// or int sum(int *, int);
// or int sum(int integers[], int n); - Any non-negative integer can be written
// or int sum(int [], int);           - inside []. It will get ignored anyway.


int main(void)
{

    int integers[] = {0,1,2,3,4,5,6,7,8,9};

    printf("The sum is %d\n",
           sum(integers, sizeof integers / sizeof integers[0]));

    return 0;

}


int sum(int integers[], int size)
// or int sum(int integers[], int size)
{

    int sum = 0;

    for (int i = 0; i < size; i++)
        sum += integers[i];

    return sum;

}





/* Trivia

 * If an array isn't initialized (i.e. only declared), then its elements, like
   uninitialized ordinary variables, get garbage values.
   But, if an array is partially initialized, then its remaining elements are
   set to 0 (no warnings are given).
   [For eg., (a) int arr[4]; - all elements have garbage values
             (b) int arr[4] = {1,2}; - arr[2] and arr[3]'s values are 0]
 * Over-initialized arrays give a warning.
   For eg., int arr[2] = {1,2,3};

 * One way to get the size of an array is to divide sizeof arr by sizeof arr[0].
   [sizeof arr gives the size of the whole array in bytes, and sizeof arr[0]
    gives the size of the first element (or, logically, the size of any element)
    of the array in bytes]

 * int arr[9] = {31, 28, [4] = 31, 30, 31, [1] = 29};
   [arr[0] has the value 31
    arr[1] has the value 29 (and not 28, as it gets overridden by [1] = 29)
    arr[2] has the value 0
    arr[3] has the value 0
    arr[4] has the value 31
    arr[5] has the value 30
    arr[6] has the value 31
    arr[7] has the value 0
    arr[8] has the value 0]

 * Before C99, only constant integer expressions greater than 0 could be used to
   specify the size of an array.
   [Similar rules to that of switch case labels apply]
 * With C99, variables can also be used to specify the size of an array. This
   is considered to be a new breed of arrays, called the variable-lenth arrays,
   or VLAs for short.
 * C11 made VLAs optional.
 * VLAs can't be initialized, and can only be declared.

 * float arr[5][12]; creates an array of 5 arrays of 12 floats each.
   This can be viewed as a two dimensional array having 5 rows and 12 columns,
   although this is just a convenient way of visualising an array with two
   indices. Internally, such an array is stored sequentially, beginning with the
   first 12-element array, followed by the second 12-element array, and so on.
   [arr is a five-element array of 12-element arrays of floats
    arr[0] is an array of 12 floats
    arr[0][0] is a float
    and so on]
   [Similar logic for arrays with more than 2 indices]
 * Initializations for multidimensional arrays can be done like
   int arr[2][3] = { {1,2,3}, {4,5,6} }; or
   int arr[2][3] = {1,2,3,4,5,6}; (not preferred) or
   int arr[2][3] =
   {
       {1,2,3},
       {4,5,6}
   };
 * In initializations, int arr[] and int arr[][3] work, but int arr[][] doesn't,
   as the initialization of a multidimensional array must have bounds for all
   dimensions except the first. Providing a bound for the first dimension is
   optional.


 * In a way, arrays are simply a disguised use of pointers.

 * An array name is also the address of the first element of the array.
   Thus, arr == &arr[0].
   This rule applies only when talking about addresses. For eg.,
   sizeof arr != sizeof &arr[0].
   printf("%p %p\n", arr, &arr[0]); would print the same address twice.

 * int arr[] = {1,2,3};
   Here, (a) arr/&arr[0] and &arr represent the same address.
         (b) arr/&arr[0] has the data type int * (i.e. pointer to an integer),
             whereas &arr has the type int (*)[3].

 * int arr[][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
   Here, (a) arr/&arr[0], arr[0]/&arr[0][0] and &arr represent the same address.
         (b) arr/&arr[0] has the data type int (*)[3], arr[0]/&arr[0][0] has the
             data type int *, and &arr has the data type int (*)[2][3].

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

   Of course, arr[3], arr[4], etc. are out of bounds, but their addresses can
   be used like &arr[3], &arr[4], etc. by the logic of pointers discussed below.
   As always, dealing with the values at invalid indexes is undefined behaviour.

   [Similarly for higher dimensions]

 * When an integer constant or an int variable is added to / subtracted from a
   pointer, then the resultant address is given according to the data type.
   This is also a reason why pointer declarations require the information of the
   data type the pointer would be pointing to.
   Note that two pointers can't be added, multiplied, etc.
   [For eg., (a) int a; int * p = &a; printf("%p %p\n", p, p+1); printed
                 0x7ffcebaba3ac 0x7ffcebaba3b0 on this system, at some time.
                 Note that the addresses of entities remain constant only for
                 the duration of the program, and the same entities may be given
                 different addresses the next time the program is run.
                 On this system, an int variable takes up 4 bytes. So, since p
                 is a pointer to an integer, therefore the second address will
                 always be 4 bytes ahead of the first address.
                 So, p+1 essentially means the address of the 4th byte ahead of
                 p.
             (b) short a = -3; short * p = &a; printf("%p %p\n", p, p+a);
                 0x7ffcf51946ee 0x7ffcf51946e8
                 On this system, a short variable takes up 2 bytes. So, since p
                 is a pointer to a short, therefore the second address will
                 always be 6 bytes behind the first address.]

 * For arrays, it means that arr == &arr[0], arr+1 == &arr[1], and so on.
   Also, *arr == arr[0], *(arr+1) == arr[1], and so on.
   Thus, in essence, we have two different notations (arrays and pointers) for
   the same thing. The C Standard also describes arrays in terms of pointers.
   For eg., arr[n] is defined as *(ar+n).
   [Similar logic for multidimensional arrays]
 * For pointers, as in this program, p[1] == *(p+1), etc.
   [Note that the variable integers is no longer an array inside the sum
    function, and is now a pointer]

 */
