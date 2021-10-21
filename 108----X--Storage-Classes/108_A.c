// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include "108.h"


int count = 0;


static void report_count(void);


int main(void)
{

    int value;
    printf("Enter a positive integer (0 to quit): ");

    while ((scanf("%d", &value) == 1) && (value > 0))
    {
        count++;

        for (register int i = value; i >= 0; i--)
            add(i, value);

        printf("Enter a positive integer (0 to quit): ");
    }

    report_count();

    return 0;

}


static void report_count(void)
{
    printf("Loop executed %d times\n", count);
}





/* Trivia - 108_A.c

 * In C, the term 'object' means a chunk of memory which can store one or more
   values. An object might not always have a stored value, but it will be of the
   right size to hold an appropriate value.
   [The term 'object' in object-oriented programming has a different meaning.
    C is not an object-oriented programming language.]

 * For eg., (a) int x; declares an identifier x, which is used to designate /
                refer to an object of data type 'int' (i.e. an object that can
                store a value of data type 'int'). x is a modifiable lvalue.
            (b) int * p = &x; - p is an identifier which designates an object of
                data type 'pointer to int' (i.e. an object that can store a
                value of data type 'pointer to int'). A value of data type
                'pointer to int' is the address of the first byte of another
                object of data type 'int'.
                p is a modifiable lvalue.
                As opposed to p, *p is not an identifier, but it also designates
                an object, i.e. the same object that x designates. *p is also a
                modifiable lvalue.
            (c) a+2*b is neither an identifier nor an lvalue, but *(a+2*b) is a
                modifiable lvalue.
            (d) const char * p = "KJ"; declares an identifier p which designates
                the object holding the address of the string "KJ". p is a
                modifiable lvalue, whereas *p is a non-modifiable lvalue.

 * An object can be described in terms of its storage duration, which means how
   long the object stays in memory, and an identifier can be described by its
   scope and its linkage, which together indicate which parts of a program can
   use the identifier.


 * A C variable name has one of the following scopes: block scope, function
   scope, function prototype scope or file scope.
 * A block is the region of code between braces (which includes the braces of
   a function definition), or the code controlled by a for/while/do-while loop
   or an if statement.
   A variable defined inside a block has block scope, and is visible from the
   point it is defined until the end of the block containing the definition.
   The function parameters, even though they occur before the opening brace of
   a function, have block scope, as they declare variables to be used inside the
   function.
   [Passing addresses to functions in order to make local variables accessible
    from other functions doesn't violate the block scope rules, as the variable
    names are still not accessible from those functions, and can only be used in
    an indirect manner (i.e. through pointer variables local to those
    functions)]
   [Even if two functions have local variables with the same name, they will be
    independent of each other and will be stored in different memory locations]
 * Function scope applies only to labels used with goto statements. This means
   that if a label first appears inside an inner block, its scope still extends
   to the entire function, and not just that inner block.
 * Function prototype scope runs from the point the variable is defined to the
   end of the prototype declaration. This means that the variable names used for
   function prototypes don't matter.
 * A variable with its definition placed outside of any function has file scope,
   and is visible from the point it is defined to the end of the file containing
   the definition.
   Because they can be used in more than one function, file scope variables are
   also called global variables.

 * A C variable has one of the following linkages: external linkage, internal
   linkage or no linkage.
 * Variables with block scope, function scope or function prototype scope have
   no linkage. This means that they are private to the block, function or
   protoype in which they are defined, respectively.
 * A file scope variable with external linkage can be used anywhere in a
   multi-file program, whereas a file scope variable with internal linkage can
   be used anywhere in a single translation unit.
   [A translation unit consists of a single C file, alongwith the included
    header files, since the preprocessor basically copy-pastes the contents of
    the header files into the C file in which they are included]
 * File scope variables with external linkage are declared without using the
   static keyword, whereas file scope variables with internal linkage need to be
   declared using the static keyword.
   For eg., #include <stdio.h>
            int a;         // file scope with external linkage
            static int b;  // file scope with internal linkage
            ...

 * A C object has one of the following storage durations: static storage
   duration, thread storage duration, automatic storage duration or 'allocated
   storage duration (discussed later)'.
 * If an object has static storage duration, then it exists throughout program
   execution. File scope variables designate objects having static storage
   duration.
   [For file scope variables, the keyword static indicates the linkage type, and
    not the storage duration. The storage duration of all file scope variables
    is static, irrespective of whether they have exernal linkage or internal
    linkage.]
 * Thread storage duration comes into play in concurrent programming, in which
   program execution can be divided into multiple threads. An object with thread
   storage duration exists from when it’s declared until the thread terminates.
   Such an object is created when a declaration that would otherwise create a
   file scope object is modified with the keyword _Thread_local. When a variable
   is declared with this specifier, each thread gets its own private copy of
   that variable.
 * Variables with block scope normally designate objects having automatic
   storage duration. These variables have memory allocated for them when the
   program enters the block in which they are defined, and the memory is freed
   when the block is exited. For eg., after a function call terminates, the
   memory it used for its variables can be used to hold variables for the next
   function that is called.
   [VLAs provide a slight exception in that they exist from the point of
    declaration to the end of the block, as opposed to from the beginning of the
    block to the end. This is because for VLAs, it is not possible to know in
    advance how much memory to allocate.]
 * In order to make a block scope variable designate an object having static
   storage duration (as opposed to automatic storage duration, which is
   default), the keyword static is used. For eg., static int x;
   [These variables exist from the time the program is loaded until the program
    terminates. But, they still have block scope.]

 * A variable belonging to the automatic storage class has automatic storage
   duration, block scope and no linkage. By default, any variable declared in a
   block or a function header belongs to the automatic storage class.
   However, one can explicitly mention the storage class as auto int x;, etc.,
   in order to make their intentions clear.
   [In C++, the keyword auto is used for a different purpose. Thus, not using
    the auto keyword in C is better for C/C++ compatibility.]
 * When a variable is declared in an inner block having the same name as another
   variable in the outer block, it is said that the inner variable hides the
   outer variable. Both the variables are still independent, but when the
   program is inside the inner block, the inner variable takes precedence over
   the outer variable.
   For eg., int x = 1; int y = 22;
            {
                int x = 2;
                printf("%d %d, ", x, y);
            }
            printf("%d %d\n", x, y);
            prints 2 22, 1 22
 * Automatic variables are not initialized unless done so explicitly.

 * A variable belonging to the register storage class also has automatic storage
   duration, block scope and no linkage, but is stored in CPU registers (or,
   more generally, in the fastest memory available) as opposed to in computer
   memory. Also, the addresses of register variables can't be taken.
 * A register variable can be declared by using the keyword register. For eg.,
   register int x;
 * Declaring a register variable is more like a request to the compiler than a
   direct order. The compiler will only store the varible in a register if it is
   feasible. Otherwise, the variable becomes an ordinary automatic variable, and
   its address can still not be taken.
 * Function parameters can also be requested to be register variables, such as
   void func(register int n).

 * A variable belonging to the static storage class with block scope has static
   storage duration, block scope and no linkage (as discussed above).
   [These variables are also known as local static variables]
 * Although these variables have block scope (i.e. they can't be accessed
   outside of the block they are defined in), they don't vanish when the
   containing block ends its job. The computer remembers their values throughout
   the execution of the program.
 * These variables are initialized only once (i.e. if a block containing the
   initialization of a static variable is called multiple times, then only the
   first initialization will be considered, and the subsequent initializations
   will be discarded).
   This is because having a statement such as static int x = 1; or simply
   static int x; inside a block only means that the scope of that variable is
   limited to that block. The variable is already in place with the initial
   value when the program is loaded into memory. So, in essence, the program
   seems to skip that line.
   [For eg.,
    (a) for (int i = 0; i < 5; i++) { int x = 1; printf("%d ", x); x++; }
        prints 1 1 1 1 1
    (b) for (int i = 0; i < 5; i++) { static int x = 1; printf("%d ", x); x++; }
        prints 1 2 3 4 5]
 * Static variables are initialized to zero if not done so explicitly.
 * Function parameters cannot be declared as static variables, i.e.
   void func(static int n), etc. are not allowed.

 * A variable belonging to the static storage class with external linkage has
   static storage duration, file scope and external linkage.
   [These variables are also known as external variables]
 * These variables can be defined by placing their definitions outside of any
   function.
   In addition to this, as a matter of documentation, they can again be declared
   (and not initialized) in the same source code file inside the function using
   them by using the keyword extern.
   [If a particular external variable is defined in one source code file and is
    used in a second source code file, then declaring the variable in the second
    file with the keyword extern is mandatory]
   [Basically, the keyword extern simply means that the actual definition of the
    extern variable is somewhere else]
 * If a block scope variable with the same name as an external variable is
   declared in a block, then a similar logic as when a variable with the same
   name as another variable in the outer block is declared in the inner block
   applies.
 * External variables are also initialized to zero if not done so explicitly.
 * Unlike automatic variables, external variables can only be initialized using
   constant expressions.

 * A variable belonging to the static storage class with internal linkage has
   static storage duration, file scope and internal linkage.
 * These variables can be defined by placing their definitions outside of any
   function using the keyword static.
   In addition to this, as a matter of documentation, they can again be declared
   (and not initialized) in the same source code file inside the function using
   them by using the keyword extern.
   [Basically, the keyword extern simply means that the actual definition of the
    extern variable is somewhere else]
 * If a block scope variable with the same name as a static variable with
   internal linkage is declared in a block, then a similar logic as when a
   variable with the same name as another variable in the outer block is
   declared in the inner block applies.
 * Static variables with internal linkage are also initialized to zero if not
   done so explicitly.
 * Unlike automatic variables, static variables with internal linkage can only
   be initialized using constant expressions.


 * As a good practice, global variables should never be used, unless they
   represent const data.


 * A C function can be either external (the default), static or 'inline
   (discussed later)'.
 * Using the keyword extern for external functions is redundant.
 * An external function can be accessed by functions in other files, but a
   static function can be used only within the defining file.


 * Type qualifiers in C (such as const, volatile, restrict and _Atomic) can be
   used more than once in a declaration, and the extraneous ones will be
   ignored.
   For eg., const const const int n = 6; is the same as const int n = 6;.

 * The volatile type qualifier tells the compiler that a variable can have its
   value altered by agencies other than the program. It is typically used for
   hardware addresses and for data shared with other programs or threads
   running simultaneously.
   For eg., an address might hold the current clock time. The value at that
   address changes as time changes, regardless of what the program is doing.

 * The restrict keyword enhances computational support by giving the compiler
   permission to optimize certain kinds of code. It can be applied only to
   pointers, and it indicates that a pointer is the sole initial means of
   accessing an object.
   For eg., in int arr[10]; int * p = arr;, p is neither the initial nor the
   sole means of access to the data in arr, but in
   int * restrict q = (int *) malloc(10 * sizeof (int));, q is the sole initial
   means of access to the memory allocated by malloc().
   Thus, p should never be qualified as restrict, whereas q can be.
 * For eg., for (int i = 0; i < 10; i++)
            {
                p[i] += 5;
                q[i] += 5;
                p[i] += 3;
                q[i] += 3;
            }
            Here, since q is a restrict variable, the compiler can reduce the
            statements q[i] += 5; and q[i] += 3; to a single statement
            q[i] += 8;.
            But, since p isn't a restrict variable, the compiler cannot do this
            optimization for p, even if it would be logically correct.



 * Due to the inclusion of 108.h, int count = 0; and extern int count; both
   appear in 108_A.c
   But, it's valid to have the defining declaration and an extern declaration in
   the same file, as long as the declarations agree in type.

 * End of Trivia */
