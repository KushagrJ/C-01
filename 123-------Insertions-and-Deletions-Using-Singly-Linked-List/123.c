// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdlib.h>


struct node
{
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
         "*   8        Exit                   *\n"
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
    current->next = new;

}

void delete_at_beginning(Node** ptr_head)
{

    Node* temp_node = *ptr_head;
    *ptr_head = (*ptr_head)->next;
    free(temp_node);

}

void delete_after_node(Node* current)
{

    Node* temp_node = current->next;
    current->next = temp_node->next;
    free(temp_node);

}





/* Trivia -

 * In this program, a singly linked list has been implemented maintaining only
   a head pointer.

 * For arbitrary insertions and deletions using a singly linked list when only a
   head pointer is maintained :-
   (Checking for out-of-range indices/positions is necessary)

   Cases for insertion :-
   1. The SLL is currently empty / non-empty (i.e. the current number of nodes
      in the SLL doesn't matter) and then insertion is done at the beginning
      (the head changes).
   2. The SLL is currently non-empty (i.e. head != NULL) and then insertion is
      done after a node (the head does not change).
   [When the SLL is empty (i.e. head == NULL), then insertion at end is the same
    as insertion at beginning]

   Cases for deletion :-
   1. The SLL is currently non-empty (i.e. head != NULL) and then deletion is
      done at the beginning (the head changes).
   2. The SLL is currently non-empty (i.e. head != NULL) and then deletion is
      done after a node (the head does not change).
   [When the SLL contains only one node (i.e. head->next == NULL), then deletion
    at end is the same as deletion at beginning]

 * End of Trivia */
