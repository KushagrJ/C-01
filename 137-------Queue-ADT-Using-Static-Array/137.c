// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>


#define QUEUE_SIZE 10


struct student_roll_number_and_gpa
{
    unsigned roll_number;
    double gpa;
};

typedef struct student_roll_number_and_gpa Item;


struct queue
{
    Item queue[QUEUE_SIZE];
    ssize_t index_of_front_item;
    ssize_t index_of_rear_item;
};

// To hide the exact implementation details from the main() function.
typedef struct queue Queue;


// Argument 1: Address of the item which is to be printed.
void print_item(Item*);

// Argument 1: Address of a Queue variable.
void create_empty_queue(struct queue*);

// Argument 1: Address of a Queue variable.
// Argument 2: Address of the item which is to be enqueued.
void enqueue(struct queue*, Item*);

// Argument 1: Address of a Queue variable.
// Argument 2: Address of the item to which the front item is to be assigned.
void peek(struct queue*, Item*);

// Argument 1: Address of a Queue variable.
void dequeue(struct queue*);

// Argument 1: Address of a Queue variable.
// Return Value: Bool value depicting whether the queue is empty.
bool is_empty(struct queue*);

// Argument 1: Address of a Queue variable.
// Return Value: Bool value depicting whether the queue is full.
bool is_full(struct queue*);


int main(void)
{

    puts("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
         "*                                                         *\n"
         "*   STUDENT QUEUE OF ROLL NUMBERS & GPAs                  *\n"
         "*                                                         *\n"
         "*                                                         *\n"
         "*   Choice   Operation                                    *\n"
         "*                                                         *\n"
         "*   1        Insert a new student's details at the        *\n"
         "*            rear of the queue                            *\n"
         "*                                                         *\n"
         "*   2        Display the queue (first in, first out)      *\n"
         "*                                                         *\n"
         "*   3        Remove the front student's details from      *\n"
         "*            the queue                                    *\n"
         "*                                                         *\n"
         "*   4        Check whether the queue is empty             *\n"
         "*                                                         *\n"
         "*   5        Check whether the queue is full              *\n"
         "*                                                         *\n"
         "*   6        Exit                                         *\n"
         "*                                                         *\n"
         "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");


    Queue students;
    create_empty_queue(&students);
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
                printf("\nThe queue is full\n");
            }

            else
            {
                printf("\nEnter the student's roll number: ");
                scanf("%u", &temp_item.roll_number);

                printf("Enter their GPA: ");
                scanf("%lf", &temp_item.gpa);

                enqueue(&students, &temp_item);

                print_item(&temp_item);

                printf("\nStudent details inserted successfully!\n");
            }
        }

        else if (choice == 2)
        {
            if (is_empty(&students))
            {
                printf("\nThe stack is empty!\n");
            }

            else
            {
                Queue temp_queue;
                create_empty_queue(&temp_queue);

                while (!is_empty(&students))
                {
                    peek(&students, &temp_item);
                    dequeue(&students);
                    print_item(&temp_item);
                    enqueue(&temp_queue, &temp_item);
                }

                while (!is_empty(&temp_queue))
                {
                    peek(&temp_queue, &temp_item);
                    dequeue(&temp_queue);
                    enqueue(&students, &temp_item);
                }
            }
        }

        else if (choice == 3)
        {
            if (is_empty(&students))
            {
                printf("\nThe queue is empty!\n");
            }

            else
            {
                dequeue(&students);
                printf("\nStudent details removed successfully!\n");
            }
        }

        else if (choice == 4)
        {
            if (is_empty(&students))
                printf("\nThe queue is empty!\n");
            else
                printf("\nThe queue is not empty!\n");
        }

        else if (choice == 5)
        {
            if (is_full(&students))
                printf("\nThe queue is full!\n");
            else
                printf("\nThe queue is not full!\n");
        }

        else if (choice == 6)
        {
            break;
        }
    }


    return 0;

}


void print_item(Item* ptr_item)
{
    printf("\nRoll No.: %u\n", ptr_item->roll_number);
    printf("GPA: %.1f/10\n", ptr_item->gpa);
}


void create_empty_queue(struct queue* ptr_queue)
{
    ptr_queue->index_of_front_item = -1;
    ptr_queue->index_of_rear_item = -1;
}


void enqueue(struct queue* ptr_queue, Item* ptr_item)
{
    if (ptr_queue->index_of_front_item == -1)
        ptr_queue->index_of_front_item = 0;

    (ptr_queue->index_of_rear_item)++;
    memmove((ptr_queue->queue) + (ptr_queue->index_of_rear_item),
            ptr_item, sizeof (Item));
}


void peek(struct queue* ptr_queue, Item* ptr_item)
{
    *ptr_item = *((ptr_queue->queue) + (ptr_queue->index_of_front_item));
}


void dequeue(struct queue* ptr_queue)
{
    // i.e. the queue will be "reset" after this dequeue operation.
    if (ptr_queue->index_of_front_item == ptr_queue->index_of_rear_item)
    {
        ptr_queue->index_of_front_item = -1;
        ptr_queue->index_of_rear_item = -1;
    }

    else
    {
        (ptr_queue->index_of_front_item)++;
    }
}


bool is_empty(struct queue* ptr_queue)
{
    if (ptr_queue->index_of_front_item == -1)
        return true;
    else
        return false;
}


bool is_full(struct queue* ptr_queue)
{
    if (ptr_queue->index_of_rear_item == QUEUE_SIZE - 1)
        return true;
    else
        return false;
}





/* Trivia -

 * In this program, a queue ADT is implemented using a static array which can
   contain a fixed number of items.
   Each item consists of the roll number and GPA of a student.

 * The following operations can be performed on such a queue :-
   (1) Creating an empty queue.
   (2) Inserting an item at the rear of a queue (i.e. enqueueing).
   (3) Retrieving the item at the front of a queue (i.e. peeking).
   (4) Removing the item at the front of a queue (i.e. dequeueing).
   (5) Determining whether a queue is empty.
   (6) Determining whether a queue is full.

 * Displaying a queue isn't a standard queue operation.

 * One drawback in the static-array-implementation of queues is that a queue is
   reported to be full whenever (index_of_rear_item == QUEUE_SIZE - 1),
   irrespective of the value of index_of_front_item.
   Thus, for eg., if QUEUE_SIZE is 10, and (at some instant) index_of_front_item
   is 5 & index_of_rear_item is 9, then also the queue will be reported as full,
   even though only 5 items are present in the queue.
   This drawback also exists in the dynamic-array-implementation of queues, as
   the memory, no matter how large, is still finite.
   But, this drawback doesn't exist in the linked-list-implementation of queues,
   as the nodes are freed immmediately after dequeueing.
 * Note that the procedure used in this program to display a queue re-creates
   the queue, thereby storing the items starting with index 0, no matter their
   previous indices.


 * In this program, const is avoided completely.

 * End of Trivia */
