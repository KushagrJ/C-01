#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "123.h"


void print_item(Item * ptr_item)
{
    printf("Roll No. - %u\n", ptr_item->rollNumber);
    printf("GPA - %.1f/10\n", ptr_item->gpa);
}


Node * create_empty_list(void)
{
    return NULL;
}


_Bool list_is_empty(Node ** ptr_head)
{
    if (*ptr_head == NULL)
        return 1;
    else
        return 0;
}


size_t number_of_items_in_list(Node ** ptr_head)
{

    (*ptr_head)->item.gpa = 5.0;

    Node * current = *ptr_head;

    size_t i = 0;
    while (current)
    {
        current = current->next;
        i++;
    }

    return i;

}


void apply_function_to_item(Node ** ptr_head, ssize_t index,
                            void (* func)(Item *))
{

    Node * current = *ptr_head;

    if (index == -1)
    {
        while (current)
        {
            (*func)(&(current->item));
            current = current->next;
        }
    }

    else
    {
        for (size_t i = 0; i != (size_t) index; i++)
            current = current->next;
        (*func)(&(current->item));
    }

}


void insert_item_in_list(Node ** ptr_head, ssize_t index, Item * ptr_item)
{

    Node * current = *ptr_head;
    Node * previous = NULL;

    if (index == -1)
    {
        while (current)
        {
            previous = current;
            current = current->next;
        }
    }

    else
    {
        for (size_t i = 0; i != (size_t) index; i++)
        {
            previous = current;
            current = current->next;
        }
    }

    Node * new = (Node *) malloc(sizeof (Node));
    if (new == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation!\n");
        exit(EXIT_FAILURE);
    }
    memmove(&(new->item), ptr_item, sizeof (Item));

    if (previous == NULL) // i.e. new points to the first node.
        *ptr_head = new;
    else
        previous->next = new;
    new->next = current;

}


void empty_list(Node ** ptr_head)
{

    Node * current = *ptr_head;

    while (current)
    {
        Node * next = current->next;
        free(current);
        current = next;
    }

}
