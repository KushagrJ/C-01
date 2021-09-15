#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "123.h"


void print_item(Item * ptr_item)
{
    printf("\nRoll No. - %u\n", ptr_item->rollNumber);
    printf("GPA - %.1f/10\n", ptr_item->gpa);
}


Node * create_empty_list(void)
{
    return NULL;
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

    if (previous == NULL) // i.e. new points to the zeroth node.
        *ptr_head = new;
    else
        previous->next = new;
    new->next = current;

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


void remove_item_from_list(Node ** ptr_head, size_t index)
{

    Node * current = *ptr_head;
    Node * previous = NULL;

    for (size_t i = 0; i != index; i++)
    {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) // i.e. the zeroth node is to be removed.
        *ptr_head = current->next;
    else
        previous->next = current->next;
    free(current);

}


bool search_by_rollNumber_and_apply_function(Node ** ptr_head, Item * ptr_item,
                                             void (* func)(Item *))
{

    _Bool matchFound = false;

    Node * current = *ptr_head;

    while (current)
    {
        if ((*ptr_item).rollNumber == current->item.rollNumber)
        {
            matchFound = true;
            (*func)(&(current->item));
        }
        current = current->next;
    }

    return matchFound;

}


bool search_by_gpa_range_and_apply_function(Node ** ptr_head, double lower,
                                            double upper, void (* func)(Item *))
{

    bool matchFound = false;

    Node * current = *ptr_head;

    while (current)
    {
        if ((lower < current->item.gpa) && (current->item.gpa < upper))
        {
            matchFound = true;
            (*func)(&(current->item));
        }
        current = current->next;
    }

    return matchFound;

}


size_t number_of_items_in_list(Node ** ptr_head)
{

    Node * current = *ptr_head;

    size_t i = 0;
    while (current)
    {
        current = current->next;
        i++;
    }

    return i;

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
