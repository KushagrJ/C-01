// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define ASSUMED_STACK_SIZE 10


struct student_roll_number_and_gpa
{
    unsigned roll_number;
    double gpa;
};

typedef struct student_roll_number_and_gpa Item;


struct stack
{
    size_t current_size_of_stack;
    Item* stack;
    ssize_t index_of_top_item;
};

// To hide the exact implementation details from the main() function.
typedef struct stack Stack;


// Argument 1: Address of the item which is to be printed.
void print_item(Item*);

// Argument 1: Address of a Stack variable.
void create_empty_stack(struct stack*);

// Argument 1: Address of a Stack variable.
// Argument 2: Address of the item which is to be pushed on the top.
void push(struct stack*, Item*);

// Argument 1: Address of a Stack variable.
// Argument 2: Address of the item to which the top item is to be assigned.
void peek(struct stack*, Item*);

// Argument 1: Address of a Stack variable.
void pop(struct stack*);

// Argument 1: Address of a Stack variable.
// Return Value: Bool value depicting whether the stack is empty.
bool is_empty(struct stack*);

// Argument 1: Address of a Stack variable.
void empty_stack(struct stack*);


int main(void)
{

    puts("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
         "*                                                         *\n"
         "*   STUDENT STACK OF ROLL NUMBERS & GPAs                  *\n"
         "*                                                         *\n"
         "*                                                         *\n"
         "*   Choice   Operation                                    *\n"
         "*                                                         *\n"
         "*   1        Insert a new student's details on the top    *\n"
         "*            of the stack                                 *\n"
         "*                                                         *\n"
         "*   2        Display the stack (last in, first out)       *\n"
         "*                                                         *\n"
         "*   3        Remove the top student's details from        *\n"
         "*            the stack                                    *\n"
         "*                                                         *\n"
         "*   4        Check whether the stack is empty             *\n"
         "*                                                         *\n"
         "*   5        Exit                                         *\n"
         "*                                                         *\n"
         "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");


    Stack students;
    create_empty_stack(&students);
    Item temp_item;


    while (true)
    {
        unsigned choice;
        printf("\n\nEnter your choice: ");
        scanf("%u", &choice);

        if (choice == 1)
        {
            printf("\nEnter the student's roll number: ");
            scanf("%u", &temp_item.roll_number);

            printf("Enter their GPA: ");
            scanf("%lf", &temp_item.gpa);

            push(&students, &temp_item);

            print_item(&temp_item);

            printf("\nStudent details inserted successfully!\n");
        }

        else if (choice == 2)
        {
            if (is_empty(&students))
            {
                printf("\nThe stack is empty!\n");
            }

            else
            {
                Stack temp_stack;
                create_empty_stack(&temp_stack);

                while (!is_empty(&students))
                {
                    peek(&students, &temp_item);
                    pop(&students);
                    print_item(&temp_item);
                    push(&temp_stack, &temp_item);
                }

                while (!is_empty(&temp_stack))
                {
                    peek(&temp_stack, &temp_item);
                    pop(&temp_stack);
                    push(&students, &temp_item);
                }

                empty_stack(&temp_stack);
            }
        }

        else if (choice == 3)
        {
            if (is_empty(&students))
            {
                printf("\nThe stack is empty!\n");
            }

            else
            {
                pop(&students);
                printf("\nStudent details removed successfully!\n");
            }
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


void print_item(Item* ptr_item)
{
    printf("\nRoll No.: %u\n", ptr_item->roll_number);
    printf("GPA: %.1f/10\n", ptr_item->gpa);
}


void create_empty_stack(struct stack* ptr_stack)
{

    ptr_stack->current_size_of_stack = ASSUMED_STACK_SIZE;

    ptr_stack->stack =
        (Item*) malloc(ptr_stack->current_size_of_stack * sizeof (Item));
    if (ptr_stack->stack == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation!\n");
        exit(EXIT_FAILURE);
    }

    ptr_stack->index_of_top_item = -1;

}


void push(struct stack* ptr_stack, Item* ptr_item)
{

    if (ptr_stack->index_of_top_item ==
            (ssize_t) ((ptr_stack->current_size_of_stack) - 1))
    {
        ptr_stack->current_size_of_stack *= 2;

        Item* temp = realloc(ptr_stack->stack,
                             ptr_stack->current_size_of_stack * sizeof (Item));
        if (temp == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation!\n");
            exit(EXIT_FAILURE);
        }
        ptr_stack->stack = temp;
    }

    (ptr_stack->index_of_top_item)++;
    memmove((ptr_stack->stack) + (ptr_stack->index_of_top_item),
            ptr_item, sizeof (Item));

}


void peek(struct stack* ptr_stack, Item* ptr_item)
{
    *ptr_item = *((ptr_stack->stack) + (ptr_stack->index_of_top_item));
}


void pop(struct stack* ptr_stack)
{
    (ptr_stack->index_of_top_item)--;
}


bool is_empty(struct stack* ptr_stack)
{
    if (ptr_stack->index_of_top_item == -1)
        return true;
    else
        return false;
}


void empty_stack(struct stack* ptr_stack)
{
    free(ptr_stack->stack);
}





/* Trivia - 129.c

 * In this program, a stack ADT is implemented using a dynamic array which can
   contain a variable number of items.
   Each item consists of the roll number and GPA of a student.

 * The following operations can be performed on such a stack :-
   (1) Creating an empty stack.
   (2) Inserting an item at the top of a stack (i.e. pushing).
   (3) Retrieving the item at the top of a stack (i.e. peeking).
   (4) Removing the item at the top of a stack (i.e. popping).
   (5) Determining whether a stack is empty.
   (6) Emptying a stack.

 * Displaying a stack isn't a standard stack operation.

 * Since a dynamic array is used, therefore there is no operation available to
   determine whether a stack is full, as items can be added to the stack as long
   as the computer doesn't run out of memory.

 * End of Trivia */
