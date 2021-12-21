// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdlib.h>


struct book
{
    char* title;
    char* author;
    double price;
    struct book* next;
};

typedef struct book Node;


void get_string_from_user(char**, size_t);


int main(void)
{

    Node* head = NULL;
    Node* current;
    Node* previous;

    while (1)
    {
        printf("Enter a book title (empty line to stop): ");
        size_t assumed_size_of_bookTitle_array = 50;
        char* bookTitle = (char*) malloc(assumed_size_of_bookTitle_array);
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

        current = (Node*) malloc(sizeof (Node));

        if (head == NULL)   // i.e. current points to the zeroth node.
            head = current;
        else
            previous->next = current;
        current->next = NULL;

        current->title = bookTitle;

        printf("Enter the author: ");
        size_t assumed_size_of_author_array = 50;
        current->author = (char*) malloc(assumed_size_of_author_array);
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

        previous = current;
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
        Node* temp = head->next;
        free(head->title);
        free(head->author);
        free(head);
        head = temp;
    }

    return 0;

}


void get_string_from_user(char** ptr_string,
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

            char* temp = realloc(*ptr_string, assumed_size_of_string_array);
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

    char* temp = realloc(*ptr_string, actual_size_of_string_array);
    if (temp == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation!\n");
        exit(EXIT_FAILURE);
    }
    *ptr_string = temp;

}





/* Trivia - 122.c

 * To store an unknown number of similar data items, one technique is using a
   dynamic array, i.e. initially allocating some memory dynamically using
   malloc(), and later doubling the size of the allocated memory using realloc()
   every time the limit is reached. Once the entire data is stored, a final call
   to realloc() can be made to free the unwanted extra memory (not necessary to
   do in every program).
 * This method has a few limitations, such as extra work needs to be done to
   insert and delete items in between the existing data.
   For eg., to insert an item at the 10th position, the existing memory block
   will have to be resized to accomodate one more item, and the existing 10th
   onwards items will have to be shifted using memmove() or a loop before the
   new item can be inserted. [Similar logic for deleting an item]

 * Another method to accomplish this task is to use a linked list.
 * In C, a linked list can be created by using dynamically allocated structures
   (called nodes) that contain, in addition to some data, a pointer to the next
   structure of the same type. Multiple such structures/nodes are 'linked'
   together with each structure knowing where to find the next structure.
 * The pointer to the next structure can be set to NULL to indicate that there
   are no more structures, i.e. the current structure is the last one.
 * Another separate pointer, known as the head pointer, is used to keep track of
   the first structure in a linked list of structures.

 * Accessing items non-sequentially is slower in a linked list as compared to
   dynamic arrays.
   For eg., to access the 10th structure in a linked list, all the structures
   from 0 to 9 need to be accessed to finally get the location of the 10th
   structure, whereas in a dynamically allocated array of structures, accessing
   the 10th structure can be done by array indexing.
 * Inserting and deleting items in between the existing data is easier in a
   linked list. After locating the item at the required index (by traversing the
   linked list using a loop and a counter to know the index number), a new item
   can be easily inserted and an existing item can be easily deleted.
   [This is the main advantage of a linked list, i.e. arbitrary insertions and
    deletions can be done without reallocations]

 * In this program, a dynamic array is used to get string inputs of unknown
   lengths from the user, and a singly linked list is used for the details of an
   unknown number of different books.


 * A simple singly linked list implementation :-

   #include <stdio.h>
   #include <stdlib.h>


   struct node
   {
       int num;
       struct node* next;
   };

   typedef struct node Node;


   int main(void)
   {

       Node* head = NULL;

       Node* current;
       Node* previous;

       int num;
       printf("Enter integers (q to quit): ");

       while (scanf("%d", &num) == 1)
       {
           current = (Node*) malloc(sizeof (Node));
           current->num = num;

           if (head == NULL)
               head = current;
           else
               previous->next = current;
           current->next = NULL;

           previous = current;
       }

       if (head)
       {
           printf("Integers entered: ");
           current = head;
           while (current)
           {
               printf("%d ", current->num);
               current = current->next;
           }
           putchar('\n');
       }

       while (head)
       {
           Node* temp = head->next;
           free(head);
           head = temp;
       }

       return 0;

   }


 * A simple doubly linked list implementation :-

   #include <stdio.h>
   #include <stdlib.h>


   struct node
   {
       struct node* previous;
       int num;
       struct node* next;
   };

   typedef struct node Node;


   int main(void)
   {

       Node* head = NULL;
       Node* tail = NULL;

       Node* current;
       Node* previous;

       int num;
       printf("Enter integers (q to quit): ");

       while (scanf("%d", &num) == 1)
       {
           current = (Node*) malloc(sizeof (Node));
           current->num = num;

           if (head == NULL)
           {
               head = current;
               current->previous = NULL;
           }

           else
           {
               previous->next = current;
               current->previous = previous;
           }

           current->next = NULL;
           tail = current;

           previous = current;
       }

       if (head)
       {
           printf("Integers entered: ");
           current = head;
           while (current)
           {
               printf("%d ", current->num);
               current = current->next;
           }
           putchar('\n');
       }

       if (tail)
       {
           printf("In reverse: ");
           current = tail;
           while (current)
           {
               printf("%d ", current->num);
               current = current->previous;
           }
           putchar('\n');
       }

       while (head)
       {
           Node* temp = head->next;
           free(head);
           head = temp;
       }

       return 0;

   }

 * End of Trivia */
