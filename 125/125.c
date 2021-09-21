// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define ASSUMED_STACK_SIZE 10


struct student_rollNumber_and_gpa
{
    unsigned rollNumber;
    double gpa;
};

typedef struct student_rollNumber_and_gpa Item;


struct stack
{
    Item * stack;
    ssize_t index_of_last_item;
};

// To hide the exact implementation details from the main() function.
typedef struct stack Stack;


// Argument 1: Address of the item which is to be printed.
void print_item(Item *);

// Argument 1: Address of a Stack variable.
void create_empty_stack(struct stack *);

// Argument 1: Address of a Stack variable.
// Argument 2: Address of the item which is to be pushed.
void push(struct stack *, Item *);

// Argument 1: Address of a Stack variable.
// Argument 2: Address of the function which is to be applied to the last item.
void apply_function_to_last_item(struct stack *, void (*)(Item *));

// Argument 1: Address of a Stack variable.
void pop(struct stack *);

// Argument 1: Address of a Stack variable.
bool is_empty(struct stack *);

// Argument 1: Address of a Stack variable.
bool is_full(struct stack *);

// Argument 1: Address of a Stack variable.
void empty_stack(struct stack *);


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
         "*   5        Exit                                         *\n"
         "*                                                         *\n"
         "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");


    Stack students;
    create_empty_stack(&students);
    Item temp;


    while (true)
    {
        unsigned choice;
        printf("\n\nEnter your choice: ");
        scanf("%u", &choice);

        if (choice == 1)
        {
            printf("\nEnter the student's roll number: ");
            scanf("%u", &temp.rollNumber);

            printf("Enter their GPA: ");
            scanf("%lf", &temp.gpa);

            push(&students, &temp);

            apply_function_to_last_item(&students, print_item);
        }

        else if (choice == 2)
        {
            apply_function_to_last_item(&students, print_item);
        }

        else if (choice == 3)
        {
            pop(&students);
        }

        else if (choice == 4)
        {
            if (is_empty(&students))
                printf("\nThe stack is empty!\n");
            else
                printf("\nThe stack is not empty!\n");
        }

        else if (choice == 5)
        {
            break;
        }
    }


    empty_stack(&students);

    return 0;

}


void print_item(Item * ptr_item)
{
    printf("\nRoll No. - %u\n", ptr_item->rollNumber);
    printf("GPA - %.1f/10\n", ptr_item->gpa);
}


void create_empty_stack(struct stack * ptr_stack)
{

    ptr_stack->stack = (Item *) malloc(ASSUMED_STACK_SIZE * sizeof (Item));
    if (ptr_stack->stack == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation!\n");
        exit(EXIT_FAILURE);
    }

    ptr_stack->index_of_last_item = -1;

}


void push(struct stack * ptr_stack, Item * ptr_item)
{

    static size_t assumed_size_of_stack = ASSUMED_STACK_SIZE;

    if (ptr_stack->index_of_last_item == (ssize_t) (assumed_size_of_stack - 1))
    {
        assumed_size_of_stack *= 2;

        Item * temp = realloc(ptr_stack->stack, assumed_size_of_stack);
        if (temp == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation!\n");
            exit(EXIT_FAILURE);
        }
        ptr_stack->stack = temp;
    }

    (ptr_stack->index_of_last_item)++;
    memmove((ptr_stack->stack) + (ptr_stack->index_of_last_item),
            ptr_item, sizeof (Item));

    printf("\nStudent details inserted successfully!\n");

}


void apply_function_to_last_item(struct stack * ptr_stack,
                                 void (* func)(Item *))
{

    if (ptr_stack->index_of_last_item == -1)
    {
        printf("\nThe stack is empty!\n");
        return;
    }

    (*func)((ptr_stack->stack) + (ptr_stack->index_of_last_item));

}


void pop(struct stack * ptr_stack)
{

    if (ptr_stack->index_of_last_item == -1)
    {
        printf("\nThe stack is empty!\n");
        return;
    }

    (ptr_stack->index_of_last_item)--;

    printf("\nStudent details removed successfully!\n");

}


bool is_empty(struct stack * ptr_stack)
{
    if (ptr_stack->index_of_last_item == -1)
        return true;
    else
        return false;
}


void empty_stack(struct stack * ptr_stack)
{
    free(ptr_stack->stack);
}





/* Trivia

 * In this program, a stack ADT is implemented using a dynamic array which can
   contain a variable number of items.
   Each item consists of the roll number and GPA of a student.

 * The following operations can be performed on such a stack :-
   (1) Creating an empty stack.
   (2) Inserting an item at the end of a stack (i.e. pushing).
   (3) Operating on the item at the end of a stack.
   (4) Removing the item at the end of a stack (i.e. popping).
   (5) Determining whether a stack is empty.
   (6) Emptying a stack.

 * Since a dynamic array is used, therefore there is no operation available to
   determine whether a stack is full, as items can be added to the stack as long
   as the computer doesn't run out of memory.


 * In this program, const is avoided completely.
   Later, modify this program by using const wherever required.
   [See 111.c's Trivia (points (a), (b) and (c)]

 */
