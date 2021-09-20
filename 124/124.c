// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>


#define STACK_SIZE 10


struct student_rollNumber_and_gpa
{
    unsigned rollNumber;
    double gpa;
};

typedef struct student_rollNumber_and_gpa Item;

// To hide the fact in the prototypes and main() that a static array is used.
typedef Item Stack[STACK_SIZE];


void print_item(Item *);

void push(Stack, ssize_t * ptr_index_of_last_item, Item *);

void apply_function_to_last_item(Stack, ssize_t * ptr_index_of_last_item,
                                 void (*)(Item *));

void pop(ssize_t * ptr_index_of_last_item);

bool is_empty(ssize_t * ptr_index_of_last_item);

bool is_full(ssize_t * ptr_index_of_last_item);


int main(void)
{

    puts("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
         "*                                                         *\n"
         "*   STUDENT STACK OF ROLL NUMBERS & GPAs                  *\n"
         "*                                                         *\n"
         "*                                                         *\n"
         "*   Choice   Operation                                    *\n"
         "*                                                         *\n"
         "*   1        Insert a new student's details at the end    *\n"
         "*            of the stack                                 *\n"
         "*                                                         *\n"
         "*   2        Display the last student's details from      *\n"
         "*            the stack                                    *\n"
         "*                                                         *\n"
         "*   3        Remove the last student's details from       *\n"
         "*            the stack                                    *\n"
         "*                                                         *\n"
         "*   4        Check whether the stack is empty             *\n"
         "*                                                         *\n"
         "*   5        Check whether the stack is full              *\n"
         "*                                                         *\n"
         "*   6        Exit                                         *\n"
         "*                                                         *\n"
         "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");


    Stack students;
    ssize_t index_of_last_item = -1;
    Item temp;


    return 0;

}


void print_item(Item * ptr_item)
{
    printf("\nRoll No. - %u\n", ptr_item->rollNumber);
    printf("GPA - %.1f/10\n", ptr_item->gpa);
}


void push(Item * arr, ssize_t * ptr_index_of_last_item, Item * ptr_item)
{

    if (*ptr_index_of_last_item == STACK_SIZE)
    {
        printf("\nThe stack is full!\n");
        return;
    }

    (*ptr_index_of_last_item)++;
    memmove(arr + (*ptr_index_of_last_item), ptr_item, sizeof (Item));

}


void apply_function_to_last_item(Item * arr, ssize_t * ptr_index_of_last_item,
                                 void (* func)(Item *))
{

    if (*ptr_index_of_last_item == -1)
    {
        printf("\nThe stack is empty!\n");
        return;
    }

    (*func)(arr + (*ptr_index_of_last_item));

}


void pop(ssize_t * ptr_index_of_last_item)
{

    if (*ptr_index_of_last_item == -1)
    {
        printf("\nThe stack is empty!\n");
        return;
    }

    (*ptr_index_of_last_item)--;

}


bool is_empty(ssize_t * ptr_index_of_last_item)
{
    if (*ptr_index_of_last_item == -1)
        return true;
    else
        return false;
}


bool is_full(ssize_t * ptr_index_of_last_item)
{
    if (*ptr_index_of_last_item == STACK_SIZE)
        return true;
    else
        return false;
}





/* Trivia

 * In this program, a stack ADT is implemented using a static array which can
   contain a fixed number of items. Each item in turn consists of the roll
   number and GPA of a student.

 * The following operations can be performed on such a stack :-
   (1) Creating an empty stack.
   (2) Inserting an item at the end of a stack (i.e. pushing).
   (3) Operating on the item at the end of a stack.
   (4) Removing the item at the end of a stack (i.e. popping).
   (5) Determining whether a stack is empty.
   (6) Determining whether a stack is full.

 */
