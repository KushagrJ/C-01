// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdlib.h>


struct node
{
    struct node* previous;
    int num;
    struct node* next;
};

typedef struct node Node;


int number_of_nodes(Node*);

void insert_at_beginning(Node**, int);

// Ensure that the linked list is non-empty before calling this function.
void insert_after_node(Node*, int);

// Ensure that the linked list is non-empty before calling this function.
void delete_at_beginning(Node**);

// Ensure that the linked list is non-empty before calling this function, and
// that the node that is passed to this function is not the last node.
void delete_after_node(Node*);


int main(void)
{

    Node* head = NULL;

    puts("* * * * * * * * * * * * * * * * * * *\n"
         "*   Choice   Operation              *\n"
         "*                                   *\n"
         "*   1        Insert at beginning    *\n"
         "*   2        Insert at end          *\n"
         "*   3        Insert at position     *\n"
         "*   4        Delete at beginning    *\n"
         "*   5        Delete at end          *\n"
         "*   6        Delete at position     *\n"
         "*   7        Display forward        *\n"
         "*   8        Display reversed       *\n"
         "*   9        Exit                   *\n"
         "* * * * * * * * * * * * * * * * * * *");

    while (1)
    {
        int choice;
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int num;
            printf("Enter the integer: ");
            scanf("%d", &num);

            insert_at_beginning(&head, num);

            printf("Integer inserted successfully\n");
        }

        else if (choice == 2)
        {
            int num;
            printf("Enter the integer: ");
            scanf("%d", &num);

            if (head == NULL)   // i.e. number_of_nodes(head) == 0
            {
                insert_at_beginning(&head, num);
            }

            else
            {
                Node* current = head;
                while (current->next)
                    current = current->next;

                insert_after_node(current, num);
            }

            printf("Integer inserted successfully\n");
        }

        else if (choice == 3)
        {
            int num_of_nodes = number_of_nodes(head);

            int position;
            while (1)
            {
                printf("Enter the position: ");
                scanf("%d", &position);
                if ((0 < position) && (position <= num_of_nodes + 1))
                    break;
                printf("Invalid position\n");
            }

            int num;
            printf("Enter the integer: ");
            scanf("%d", &num);

            if (position == 1)
            {
                insert_at_beginning(&head, num);
            }

            else
            {
                Node* current = head;
                for (int i = 0; i < position - 2; i++)
                    current = current->next;

                insert_after_node(current, num);
            }

            printf("Integer inserted successfully\n");
        }

        else if (choice == 4)
        {
            if (head == NULL)   // i.e. number_of_nodes(head) == 0
            {
                printf("The list is currently empty\n");
                continue;
            }

            delete_at_beginning(&head);

            printf("Integer deleted successfully\n");
        }

        else if (choice == 5)
        {
            if (head == NULL)   // i.e. number_of_nodes(head) == 0
            {
                printf("The list is currently empty\n");
                continue;
            }

            if (head->next == NULL)   // i.e. number_of_nodes(head) == 1
            {
                delete_at_beginning(&head);
            }

            else
            {
                Node* current = head;
                while ((current->next)->next)
                    current = current->next;

                delete_after_node(current);
            }

            printf("Integer deleted successfully\n");
        }

        else if (choice == 6)
        {
            if (head == NULL)   // i.e. number_of_nodes(head) == 0
            {
                printf("The list is currently empty\n");
                continue;
            }

            int num_of_nodes = number_of_nodes(head);

            int position;
            while (1)
            {
                printf("Enter the position: ");
                scanf("%d", &position);
                if ((0 < position) && (position <= num_of_nodes))
                    break;
                printf("Invalid position\n");
            }

            if (position == 1)
            {
                delete_at_beginning(&head);
            }

            else
            {
                Node* current = head;
                for (int i = 0; i < position - 2; i++)
                    current = current->next;

                delete_after_node(current);
            }

            printf("Integer deleted successfully\n");
        }

        else if (choice == 7)
        {
            if (head == NULL)
            {
                printf("The list is currently empty\n");
                continue;
            }

            Node* current = head;
            while (current)
            {
                printf("%d ", current->num);
                current = current->next;
            }
            printf("\n");
        }

        else if (choice == 8)
        {
            if (head == NULL)
            {
                printf("The list is currently empty\n");
                continue;
            }

            Node* current = head;
            while (current->next)
                current = current->next;
            while (current)
            {
                printf("%d ", current->num);
                current = current->previous;
            }
            printf("\n");
        }

        else if (choice == 9)
        {
            break;
        }
    }

    while (head)
    {
        Node* temp_node = head->next;
        free(head);
        head = temp_node;
    }

    return 0;

}

int number_of_nodes(Node* head)
{

    int number_of_nodes = 0;

    while (head)
    {
        head = head->next;
        (number_of_nodes)++;
    }

    return number_of_nodes;

}

void insert_at_beginning(Node** ptr_head, int num)
{

    Node* new = (Node*) malloc(sizeof (Node));
    if (new == NULL)
    {
        printf("Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    new->num = num;

    new->next = *ptr_head;
    if (*ptr_head)
        (*ptr_head)->previous = new;
    new->previous = NULL;

    *ptr_head = new;

}

void insert_after_node(Node* current, int num)
{

    Node* new = (Node*) malloc(sizeof (Node));
    if (new == NULL)
    {
        printf("Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    new->num = num;

    new->next = current->next;
    if (new->next)
        (new->next)->previous = new;
    current->next = new;
    new->previous = current;

}

void delete_at_beginning(Node** ptr_head)
{

    Node* temp_node = *ptr_head;
    *ptr_head = (*ptr_head)->next;
    if (*ptr_head)
        (*ptr_head)->previous = NULL;
    free(temp_node);

}

void delete_after_node(Node* current)
{

    Node* temp_node = current->next;
    current->next = temp_node->next;
    if (temp_node->next)
        (temp_node->next)->previous = current;
    free(temp_node);

}





/* Trivia -

 * In this program, a doubly linked list has been implemented maintaining only
   a head pointer. Thus, the cases for insertion and deletion are the same as
   that for a singly linked list.
 * Maintaining a tail pointer in addition to a head pointer becomes very
   complicated due to the many cases to be considered.

 * For arbitrary insertions and deletions using a doubly linked list when a tail
   pointer is maintained in addition to a head pointer :-
   (Checking for out-of-range indices/positions is necessary)

   Cases for insertion :-
   1. The DLL is currently empty (i.e. head == NULL && tail == NULL) and then
      insertion is done at the beginning (the head and the tail both change).
   2. The DLL is currently non-empty (i.e. head != NULL && tail != NULL) and
      then insertion is done at the beginning (the head changes but the tail
      does not change).
   3. The DLL is currently non-empty (i.e. head != NULL && tail != NULL) and
      then insertion is done at the end (the tail changes but the head does not
      change).
   4. The DLL is currently non-empty (i.e. head != NULL && tail != NULL) and
      then insertion is done after a node such that node != tail (neither the
      head nor the tail changes).
   [(head == NULL && tail != NULL) and (head != NULL && tail == NULL) are
    impossible cases]
   [When the DLL is empty (i.e. head == NULL && tail == NULL), then insertion at
    end is the same as insertion at beginning]

   Cases for deletion :-
   1. The DLL is currently non-empty (i.e. head != NULL && tail != NULL),
      consists of only one node (i.e. head == tail) and then deletion is done
      (the head and the tail both change).
   2. The DLL is currently non-empty (i.e. head != NULL && tail != NULL),
      consists of more than one nodes (i.e. head != tail) and then deletion is
      done at the beginning (the head changes but the tail does not change).
   3. The DLL is currently non-empty (i.e. head != NULL && tail != NULL),
      consists of more than one nodes (i.e. head != tail) and then deletion is
      done at the end (the tail changes but the head does not change).
   4. The DLL is currently non-empty (i.e. head != NULL && tail != NULL),
      consists of more than one nodes (i.e. head != tail) and then deletion is
      done after a node such that node->next != tail (neither the head nor the
      tail changes).
   [When the DLL contains only one node (i.e. head != NULL && tail != NULL &&
    head == tail), then deletion at end is the same as deletion at beginning]

 * End of Trivia */
