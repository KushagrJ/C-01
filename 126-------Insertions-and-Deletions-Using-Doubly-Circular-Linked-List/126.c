// C17 Standard
// This program doesn't include input validation.

// ptr_next_node, ptr_current_node, ptr_previous_node, etc. are better names
// than next, current, previous, etc.

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

void insert_at_end(Node**, int);

// Ensure that the linked list is non-empty before calling this function.
void insert_after_node(Node*, int);

// Ensure that the linked list is non-empty before calling this function.
void delete_at_end(Node**);

// Ensure that the linked list is non-empty before calling this function, and
// that the node that is passed to this function is not the second last node.
void delete_after_node(Node*);


int main(void)
{

    Node* tail = NULL;

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

            if (tail == NULL)   // i.e. number_of_nodes(tail) == 0
            {
                insert_at_end(&tail, num);
            }

            else
            {
                insert_after_node(tail, num);
            }

            printf("Integer inserted successfully\n");
        }

        else if (choice == 2)
        {
            int num;
            printf("Enter the integer: ");
            scanf("%d", &num);

            insert_at_end(&tail, num);

            printf("Integer inserted successfully\n");
        }

        else if (choice == 3)
        {
            int num_of_nodes = number_of_nodes(tail);

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

            if (position == num_of_nodes + 1)
            {
                insert_at_end(&tail, num);
            }

            else
            {
                Node* current = tail;
                for (int i = 0; i < position - 1; i++)
                    current = current->next;

                insert_after_node(current, num);
            }

            printf("Integer inserted successfully\n");
        }

        else if (choice == 4)
        {
            if (tail == NULL)   // i.e. number_of_nodes(tail) == 0
            {
                printf("The list is currently empty\n");
                continue;
            }

            if (tail->next == tail)   // i.e. number_of_nodes(tail) == 1
            {
                delete_at_end(&tail);
            }

            else
            {
                delete_after_node(tail);
            }

            printf("Integer deleted successfully\n");
        }

        else if (choice == 5)
        {
            if (tail == NULL)   // i.e. number_of_nodes(tail) == 0
            {
                printf("The list is currently empty\n");
                continue;
            }

            delete_at_end(&tail);

            printf("Integer deleted successfully\n");
        }

        else if (choice == 6)
        {
            if (tail == NULL)   // i.e. number_of_nodes(head) == 0
            {
                printf("The list is currently empty\n");
                continue;
            }

            int num_of_nodes = number_of_nodes(tail);

            int position;
            while (1)
            {
                printf("Enter the position: ");
                scanf("%d", &position);
                if ((0 < position) && (position <= num_of_nodes))
                    break;
                printf("Invalid position\n");
            }

            if (position == num_of_nodes)
            {
                delete_at_end(&tail);
            }

            else
            {
                Node* current = tail;
                for (int i = 0; i < position - 1; i++)
                    current = current->next;

                delete_after_node(current);
            }

            printf("Integer deleted successfully\n");
        }

        else if (choice == 7)
        {
            if (tail == NULL)
            {
                printf("The list is currently empty\n");
                continue;
            }

            Node* current = tail->next;
            do {
                printf("%d ", current->num);
                current = current->next;
            } while (current != tail->next);
            printf("\n");
        }

        else if (choice == 8)
        {
            if (tail == NULL)
            {
                printf("The list is currently empty\n");
                continue;
            }

            Node* current = tail;
            do {
                printf("%d ", current->num);
                current = current->previous;
            } while (current != tail);
            printf("\n");
        }

        else if (choice == 9)
        {
            break;
        }
    }

    if (tail)
    {
        Node* temp_node = tail->next;
        tail->next = NULL;
        tail = temp_node;

        while (tail)
        {
            Node* temp_node_2 = tail->next;
            free(tail);
            tail = temp_node_2;
        }
    }

    return 0;

}


int number_of_nodes(Node* tail)
{

    int number_of_nodes = 0;

    Node* current = tail;

    if (tail)
    {
        do {
            number_of_nodes++;
            current = current->next;
        } while (current != tail);
    }

    return number_of_nodes;

}


void insert_at_end(Node** ptr_tail, int num)
{

    Node* new = (Node*) malloc(sizeof (Node));
    if (new == NULL)
    {
        printf("Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    new->num = num;

    if (*ptr_tail)
    {
        new->next = (*ptr_tail)->next;
        ((*ptr_tail)->next)->previous = new;

        (*ptr_tail)->next = new;
        new->previous = *ptr_tail;
    }

    else
    {
        new->next = new;
        new->previous = new;
    }

    *ptr_tail = new;

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
    (current->next)->previous = new;

    current->next = new;
    new->previous = current;

}


void delete_at_end(Node** ptr_tail)
{

    if ((*ptr_tail)->next == *ptr_tail)
    {
        free(*ptr_tail);
        *ptr_tail = NULL;
    }

    else
    {
        Node* current = (*ptr_tail)->previous;

        current->next = (*ptr_tail)->next;
        ((*ptr_tail)->next)->previous = current;
        free(*ptr_tail);
        *ptr_tail = current;
    }

}


void delete_after_node(Node* current)
{

    Node* temp_node = current->next;
    current->next = temp_node->next;
    ((temp_node)->next)->previous = current;
    free(temp_node);

}





/* Trivia - 126.c

 * In this program, a doubly circular linked list has been implemented
   maintaining only a tail pointer.

 * In a circular linked list, maintaining a head pointer in addition to a tail
   pointer is unnecessary, as head == tail->next.

 * End of Trivia */
