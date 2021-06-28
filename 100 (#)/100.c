// C17 Standard

#include <stdio.h>


int sum(int *, int);
// or int sum(int [], int);              - Any non-negative integer can be
// or int sum(int * integers, int size);   written inside []. It will get
// or int sum(int integers[], int size);   ignored anyway.


int main(void)
{

    int integers[] = {0,1,2,3,4,5,6,7,8,9};

    printf("The sum is %d\n",
           sum(integers, sizeof integers / sizeof integers[0]));

    return 0;

}


int sum(int * integers, int size)
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
 * Over-initialized arrays may give an error or simply a warning.
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
 * VLAs need to have automatic storage class (discussed later).
 * The term variable in variable-length arrays does not mean that the size of
   the array can be modified after it has been created. Once created, a VLA
   keeps the same size.

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
   int arr[2][3] = { {1,2,3},
                     {4,5,6} };
 * In initializations, int arr[] and int arr[][3] work, but int arr[][] doesn't,
   as the initialization of a multidimensional array must have bounds for all
   dimensions except the first. Providing a bound for the first dimension is
   optional.


 * In a way, arrays are simply a disguised use of pointers.

 * An array name is also the address of the first element of the array.
   Thus, arr == &arr[0].
   Technically, it is said that an array name 'decays' to a pointer that points
   to the first element of that array (implicit conversion).
 * This rule applies in most cases, with a few exceptions.
   One example of an exception - sizeof arr != sizeof &arr[0].
   Thus, after an array decays to a pointer, sizeof can no longer be used to
   know the total number of bytes used by the entire array, and sizeof in this
   case would only report the number of bytes used by the pointer, which is 8 on
   this system.
 * printf("%p %p\n", arr, &arr[0]); would print the same address twice.

 * int arr[] = {1,2,3};
   Here, (a) arr/&arr[0] and &arr represent the same address.
         (b) arr (in most cases) and &arr[0] have the data type int * (i.e.
             pointer to an integer), whereas &arr has the type int (*)[3] (i.e.
             pointer to a 3-element array of integers).

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
                 So, p+1 essentially means the address of the 4th byte ahead
                 of p.
             (b) short a = -3; short * p = &a; printf("%p %p\n", p, p+a);
                 0x7ffcf51946ee 0x7ffcf51946e8
                 On this system, a short variable takes up 2 bytes. So, since p
                 is a pointer to a short, therefore the second address will
                 always be 6 bytes behind the first address.]

 * For arrays, in most cases, it means that arr == &arr[0], arr+1 == &arr[1],
   and so on.
   Also, *arr == arr[0], *(arr+1) == arr[1], and so on.
   Thus, in essence, we have two different notations (arrays and pointers) for
   the same thing. The C Standard also describes arrays in terms of pointers.
   For eg., arr[n] is defined as *(ar+n).
   [Similar logic for multidimensional arrays]
 * For pointers, as in this program, p[1] == *(p+1), etc.
   [Note that the variable integers is no longer an array inside the sum
    function, and is now a pointer]

 * In function prototypes and headers, int * arr is equivalent to int arr[]
   because when an array expression appears in most contexts, the type of the
   expression is implicitly converted from "n-element array of type t" to
   "pointer to t", and its value is set to point to the first element in the
   array. Also, this converted expression is not an lvalue, which means that it
   can't be assigned values. So, int * p; p = &a; works, but int arr[5];
   arr = &a; doesn't.
   This implicit conversion is the reason why & is not used with
   scanf("%s", str);
   [The exceptions to this rule are when the array expression appears as an
    operand of either the & or the sizeof operators, or when it is a string
    literal being used as an initializer in a declaration.
    For eg., as discussed before, in &arr, the data type isn't converted
    implicitly]
 * The [] notation can be used to declare a pointer only in function prototypes
   and headers.
   In other contexts regarding declarations and initializations, the [] notation
   is used for arrays and the * notation is used for pointers.
 * Thus, arrays and pointers aren't exactly the same thing, but are very closely
   related.
 * For eg., when the type of arr from int arr[5] isn't implicitly converted to
   int * (i.e. when arr is just an array), then arr is simply the name of the
   space set aside for 5 contiguous integers.
   In this context, an array is different from a pointer.
 * Another difference between arrays and pointers :-
   When the compiler sees arr[3] (no implicit conversion of array), it emits
   code to start at the location "arr", move three past it, and fetch the item
   there.
   When the compiler sees p[3] (i.e. a pointer), it emits code to start at the
   location "p", fetch the pointer value there, add three to the pointer, and
   finally fetch the item pointed to.
   Although the net effect is the same in both the cases, the compiler gets
   there differently.

 * In statements like arr[3] = 25;, arr[x] < y;, etc., there is no implicit
   conversion as the data type of arr[3] is int (if arr is an array of
   integers). Thus, arr is an array, but arr[3] is not.

 * In most cases, a variable is an abstraction (a convenient name) for the
   entire memory position allocated, i.e. it consists of the address of the
   first byte alongwith the information about the number of the next contiguous
   bytes to be considered a part of it.
   [But sometimes, a variable is stored in a register instead of in memory. Then
    it doesn't have an address, and pointers can't be created to it.]
 * A pointer (which is a variable / data object) stores just the address of the
   first byte, and doesn't bother with the number of next contiguous bytes to
   consider a part of the object it's pointing to, as the data type of the
   pointer (i.e. pointer to <data type>) automatically provides that
   information.
 * So, in int a; int * p = &a;, p is a convenient name for an entire memory
   location (i.e. the first byte of p and the information that the next 7 (on
   this system) contiguous bytes are also a part of p) and the value that is
   stored in those 8 bytes of storage is just the address of the first byte
   of a.

 * A variable is not a pointer automatically dereferenced.
   A variable just holds the value it is supposed to hold.
   If it is a pointer, it will hold a memory address, if it is an integer, it
   will hold an integer value, etc.

 */