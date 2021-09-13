// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdlib.h>


void get_string_from_user(char **, size_t);


struct book
{
    char * title;
    char * author;
    double price;
    struct book * next;
};


int main(void)
{

    struct book * head = NULL;
    struct book * prev;
    struct book * current;

    while (1)
    {
        printf("Enter a book title (empty line to stop): ");
        size_t assumed_size_of_bookTitle_array = 50;
        char * bookTitle = (char *) malloc(assumed_size_of_bookTitle_array);
        if (bookTitle == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation!\n");
            exit(EXIT_FAILURE);
        }
        get_string_from_user(&bookTitle, assumed_size_of_bookTitle_array);

        if (bookTitle[0] == '\0')
        {
            free(bookTitle);
            break;
        }

        current = (struct book *) malloc(sizeof (struct book));

        if (head == NULL)
            head = current;
        else
            prev->next = current;
        current->next = NULL;

        current->title = bookTitle;

        printf("Enter the author: ");
        size_t assumed_size_of_author_array = 50;
        current->author = (char *) malloc(assumed_size_of_author_array);
        if (current->author == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation!\n");
            exit(EXIT_FAILURE);
        }
        get_string_from_user(&(current->author), assumed_size_of_author_array);

        printf("Enter the price: Rs. ");
        scanf("%lf", &current->price);
        while (getchar() != '\n')
            continue;
        printf("\n");

        prev = current;
    }


    if (head)
    {
        printf("\n\nHere are the books you entered :-\n\n");
        current = head;
        while (current)
        {
            printf("\'%s\' by %s: Rs. %g\n",
                   current->title, current->author, current->price);
            current = current->next;
        }
    }


    while (head)
    {
        struct book * next = head->next;
        free(head->title);
        free(head->author);
        free(head);
        head = next;
    }

    return 0;

}


void get_string_from_user(char ** ptr_string,
                          size_t assumed_size_of_string_array)
{

    size_t i = 0;
    int c;
    while (((c = getchar()) != '\n') && (c != EOF))
    {
        (*ptr_string)[i] = c;

        i++;
        if (i == assumed_size_of_string_array)
        {
            assumed_size_of_string_array *= 2;

            char * temp = realloc(*ptr_string, assumed_size_of_string_array);
            if (temp == NULL)
            {
                fprintf(stderr, "Unsuccessful allocation!\n");
                exit(EXIT_FAILURE);
            }
            *ptr_string = temp;
        }
    }
    (*ptr_string)[i] = '\0';

    size_t actual_size_of_string_array = i+1;

    char * temp = realloc(*ptr_string, actual_size_of_string_array);
    if (temp == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation!\n");
        exit(EXIT_FAILURE);
    }
    *ptr_string = temp;

}





/* Trivia

 * To store an unknown number of similar data items, one technique is initially
   allocating some memory dynamically using malloc(), and later doubling the
   size of the allocated memory using realloc() every time the limit is reached.
   Once the entire data is stored, a final call to realloc() can be made to free
   the unwanted extra memory.
 * This method has a few limitations, such as extra work needs to be done to add
   and remove items in between the existing data.
   For eg., to insert an item into the 10th position, the existing memory block
   will have to be resized to accomodate one more item, and the existing 10th
   onwards items will have to be shifted using memmove() or a loop before the
   new element can be inserted. [Similar logic for removing an item]

 * Another method to accomplish this task is to use a linked list.
 * In C, a linked list can be created by using dynamically allocated structures
   that contain, in addition to some data, a pointer to the next structure of
   the same type. Multiple such structures are 'linked' together with each
   structure knowing where to find the next structure.
 * The pointer can be set to NULL to indicate that there are no more structures,
   i.e. the current structure is the last one.
 * Another separate pointer, known as the head pointer, is used to keep track of
   the first structure in a linked list of structures.

 * Accessing items non-sequentially is slower in a linked list as compared to
   the realloc() method.
   For eg., to access the 10th structure in a linked list, all the structures
   from 0 to 9 need to be accessed to finally get the location of the 10th
   structure, whereas in a dynamically allocated array of structures, accessing
   the 10th structure can be done by array indexing.
 * Adding and removing items in between the existing data is easier in a linked
   list. After locating the required position (by first traversing the linked
   list using a loop and a counter to know the position number), a new item
   can be easily inserted and an existing item can be easily removed.

 * In this program, the realloc() method is used to get string inputs of
   unknown lengths from the user, and a linked list is used for the details of
   an unknown number of different books.

 */
