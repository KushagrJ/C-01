// C17 Standard

#include <stdio.h>


int sum(int *, int *);


int main(void)
{

    int integers[10] = {0,1,2,3,4,5,6,7,8,9};

    printf("The sum is %d\n", sum(integers, integers+10));

    return 0;

}


int sum(int * start, int * end)
{

    int sum = 0;

    for (int * i = start; i < end; i++)
        sum += *i;

//  for ( ; start < end; start++)
//      sum += *start;

    return sum;

}





/* Trivia

 * A function working on an array needs to know where to start and stop.
   One way to tell this to a function is by using a pointer parameter to
   identify the beginning of the array and an integer parameter to indicate the
   size of the array.
   Another way to achieve this is by passing two pointers, with the first one
   indicating where the array starts and the second one indicating where the
   array ends.
   [Generally, the ending pointer is taken to be the one pointing to the byte
    immediately after the array ends, so that the iteration can be done like
    while (i < end), etc. This approach makes the code elegant and easier to
    remember, as opposed to the ending pointer pointing to the last element of
    the array.
    This approach works because it is guaranteed that the address one past the
    end element of an array is valid.]

 * arr[i] and *(arr+i) are equivalent in meaning. Both work if arr is the name
   of an array, and both work if arr is a pointer variable.
   But, expressions like arr++ only work if arr is a pointer variable.

 * Pointer Operations :-

   (a) Assignment -
       Addresses can be assigned to a pointer. The address should be compatible
       with the pointer type.

   (b) Dereferencing -
       The * operator gives the value stored in the pointed-to location.

   (c) Taking a pointer's address -
       The & operator tells where the pointer itself is stored.

   (d) Adding/Subtracting an integer to/from a pointer -
       As discussed before. The result is a pointer.
       When dealing with decayed arrays / pointers pointing to arrays, if the
       result of addition/subtraction lies outside of the array (except for one
       past the end element), then the behaviour is undefined.
       [p+2, 2+p and p-2 work, but 2-p gives an error]
       [This works on addresses as well, for eg., &a+2, 2+&a and &a-2]

   (e) Incrementing/Decrementing a pointer

   (f) Differencing -
       The difference between two pointers of the same type can be found.
       The result is a signed integer.
       For eg., if p and q are pointers to integers, and if p-q has the value 2,
       then this means that p is ahead of q by 8 bytes on this system.
       Similarly, if p-q has the value -2, then this means that p is behind q by
       8 bytes on this system.
       Normally, differencing among pointers is done only in the same array to
       find out how far apart the elements are.
       Using differencing on random pointers of the same data type may or may
       not work.
       [This works on addresses as well, for eg., &a[1] - &a[4], etc.]

   (g) Comparison -
       Two pointers of the same data type can be compared by using the
       relational operators.

 * Uninitialized pointers must never be dereferenced.
   For eg., int * p; *p = 5; is valid, but should never be done.
   Since p is uninitialized, it points to a random location in memory. Now,
   assigning 5 to that memory location may cause the program to crash.
 * Before a pointer is used, it must be assigned a memory location that has
   already been allocated. For eg., a pointer can be assigned the address of an
   existing variable, or the malloc() function (discussed later) can be used to
   allocate memory.

 * With functions that process a fundamental type, such as int, there is a
   choice of passing the int by value or by reference (i.e. a pointer-to-int).
   The usual rule is to pass quantities by value unless the program needs to
   alter the values, in which case pointers must be passed.
 * With functions that process arrays, it is much quicker to pass pointers,
   instead of passing arrays by value (which is not possible in C, unless
   special tricks like structs are used).
 * Passing arrays by reference (i.e. passing pointers) means that the called
   functions get complete control over the arrays in the calling functions,
   and can accidentally modify the original data, even when the called functions
   only need to read the contents of the arrays.
 * To tackle this issue, the const keyword can be used in the prototypes and
   headers, like int sum(const int * arr, int size);
             and int sum(const int arr[], int size);
   Using const in this way does not require that the original array be constant.
   It just says that the called function has to treat the array as though it
   were a constant.

 * As opposed to the #define preprocessor directive, the const keyword allows
   the user to create constant arrays, constant pointers and pointers to
   constants.
   [For eg., const int arr[] = {1,2,3,4,5}; arr[2] = 6; - Error]
 * const int * ptr; declares ptr to be a pointer to a const int (in other words,
   ptr is a pointer-to-constant).
   int * const prt; declares ptr to be a constant pointer to an int (in other
   words, ptr is a constant pointer).
   [const int * is the same as int const *, and const int * const is the same
    as int const * const]
   [See http://c-faq.com/decl/spiral.anderson.html]
 * Pointers to constants can't be used to change values, but these pointers
   can be made to point somewhere else.
   [For eg., int arr[2] = {1,2}; const int * p = arr; *p = 2; - Error
             int arr[2] = {1,2}; const int * p = arr; p++; - Valid]
   It's valid to assign the addresses of either constant or non-constant data to
   pointers to constants.
   [For eg., int foo[2] = {1,2}; const int bar[2] = {3,4};
             const int * p = foo; p = bar; p = &foo[1]; - Valid]
   Only the addresses of non-constant data can be assigned to regular pointers.
   [For eg., int foo[2] = {1,2}; const int bar[2] = {3,4};
             int * p = foo; - Valid
             p = bar; - Warning/Error (any attempt to modify const data using a
                                       non-const identifier results in undefined
                                       behaviour)
             p = &foo[1]; - Valid]
 * Constant pointers can't be made to point elsewhere, but can be used to change
   values.
   [For eg., int arr[2] = {1,2}; int * const p = arr;
             p = &arr[1]; - Error
             *(p+1) = 10; - Valid]
 * Finally, in const int * const p = arr;, p is a pointer that can neither
   change where its pointing to nor change values.

 */
