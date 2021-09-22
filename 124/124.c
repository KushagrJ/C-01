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


struct stack
{
    Item stack[STACK_SIZE];
    ssize_t index_of_top_item;
};

// To hide the exact implementation details from the main() function.
typedef struct stack Stack;


// Argument 1: Address of the item which is to be printed.
void print_item(Item *);

// Argument 1: Address of a Stack variable.
void create_empty_stack(struct stack *);

// Argument 1: Address of a Stack variable.
// Argument 2: Address of the item which is to be pushed on the top.
void push(struct stack *, Item *);

// Argument 1: Address of a Stack variable.
// Argument 2: Address of the item to which the top item is to be assigned.
void peek(struct stack *, Item *);

// Argument 1: Address of a Stack variable.
void pop(struct stack *);

// Argument 1: Address of a Stack variable.
// Return Value: A bool value depicting whether the stack is empty.
bool is_empty(struct stack *);

// Argument 1: Address of a Stack variable.
// Return Value: A bool value depicting whether the stack is full.
bool is_full(struct stack *);


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
         "*   2        Display the stack                            *\n"
         "*                                                         *\n"
         "*   3        Remove the top student's details from        *\n"
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
    create_empty_stack(&students);
    Item temp_item;


    while (true)
    {
        unsigned choice;
        printf("\n\nEnter your choice: ");
        scanf("%u", &choice);

        if (choice == 1)
        {
            if (is_full(&students))
            {
                printf("\nThe stack is full!\n");
            }

            else
            {
                printf("\nEnter the student's roll number: ");
                scanf("%u", &temp_item.rollNumber);

                printf("Enter their GPA: ");
                scanf("%lf", &temp_item.gpa);

                push(&students, &temp_item);

                printf("\nStudent details inserted successfully!\n");

                print_item(&temp_item);
            }
        }

        else if (choice == 2)
        {
            Stack temp_stack;
            create_empty_stack(&temp_stack);

            while (true)
            {
                if (is_empty(&students))
                    break;

                peek(&students, &temp_item);
                push(&temp_stack, &temp_item);
                pop(&students);
            }

            if (is_empty(&temp_stack))
            {
                printf("\nThe stack is empty!\n");
            }

            else
            {
                while (true)
                {
                    if (is_empty(&temp_stack))
                        break;

                    peek(&temp_stack, &temp_item);
                    print_item(&temp_item);
                    push(&students, &temp_item);
                    pop(&temp_stack);
                }
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
            if (is_full(&students))
                printf("\nThe stack is full!\n");
            else
                printf("\nThe stack is not full!\n");
        }

        else if (choice == 6)
        {
            break;
        }
    }


    return 0;

}


void print_item(Item * ptr_item)
{
    printf("\nRoll No. - %u\n", ptr_item->rollNumber);
    printf("GPA - %.1f/10\n", ptr_item->gpa);
}


void create_empty_stack(struct stack * ptr_stack)
{
    ptr_stack->index_of_top_item = -1;
}


void push(struct stack * ptr_stack, Item * ptr_item)
{
    (ptr_stack->index_of_top_item)++;
    memmove((ptr_stack->stack) + (ptr_stack->index_of_top_item),
            ptr_item, sizeof (Item));
}


void peek(struct stack * ptr_stack, Item * ptr_item)
{
    *ptr_item = *((ptr_stack->stack) + (ptr_stack->index_of_top_item));
}


void pop(struct stack * ptr_stack)
{
    (ptr_stack->index_of_top_item)--;
}


bool is_empty(struct stack * ptr_stack)
{
    if (ptr_stack->index_of_top_item == -1)
        return true;
    else
        return false;
}


bool is_full(struct stack * ptr_stack)
{
    if (ptr_stack->index_of_top_item == STACK_SIZE - 1)
        return true;
    else
        return false;
}





/* Trivia

 * In this program, a stack ADT is implemented using a static array which can
   contain a fixed number of items.
   Each item consists of the roll number and GPA of a student.

 * The following operations can be performed on such a stack :-
   (1) Creating an empty stack.
   (2) Inserting an item at the end of a stack (i.e. pushing).
   (3) Operating on the item at the end of a stack.
   (4) Removing the item at the end of a stack (i.e. popping).
   (5) Determining whether a stack is empty.
   (6) Determining whether a stack is full.


 * In this program, const is avoided completely.
   Later, modify this program by using const wherever required.
   [See 111.c's Trivia (points (a), (b) and (c)]

 */
