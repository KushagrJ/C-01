#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "123.h"


void print_item(Item * ptr_item, size_t index)
{
    printf("\n%2zu", index + 1);
    printf("     Roll No. - %u\n", ptr_item->rollNumber);
    printf("       GPA - %.1f/10\n", ptr_item->gpa);
}


Node * create_empty_list(void)
{
    return NULL;
}


size_t insert_item_in_list(Node ** ptr_head, ssize_t index, Item * ptr_item)
{

    size_t index_of_inserted_item;

    Node * current = *ptr_head;
    Node * previous = NULL;

    size_t i = 0;

    if (index == -1)
    {
        while (current)
        {
            previous = current;
            current = current->next;
            i++;
        }
    }

    else
    {
        while (i != (size_t) index)
        {
            previous = current;
            current = current->next;
            i++;
        }
    }

    index_of_inserted_item = i;

    // new is to be inserted in between previous and current.

    Node * new = (Node *) malloc(sizeof (Node));
    if (new == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation!\n");
        exit(EXIT_FAILURE);
    }
    memmove(&(new->item), ptr_item, sizeof (Item));

    if (previous == NULL)   // i.e. new points to the zeroth node.
        *ptr_head = new;
    else
        previous->next = new;
    new->next = current;

    printf("\nStudent details inserted successfully!\n");

    return index_of_inserted_item;

}


void apply_function_to_item(Node ** ptr_head, ssize_t index,
                            void (* func)(Item *, size_t))
{

    if (*ptr_head == NULL)
    {
        printf("\nThe list is currently empty!\n");
        return;
    }

    Node * current = *ptr_head;

    if (index == -1)
    {
        for (size_t i = 0; current; i++)
        {
            (*func)(&(current->item), i);
            current = current->next;
        }
    }

    else
    {
        for (size_t i = 0; i != (size_t) index; i++)
            current = current->next;
        (*func)(&(current->item), index);
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

    if (previous == NULL)   // i.e. the zeroth node is to be removed.
        *ptr_head = current->next;
    else
        previous->next = current->next;
    free(current);

    printf("\nStudent details removed successfully!\n");

}


void search_by_rollNumber_and_apply_function(Node ** ptr_head, Item * ptr_item,
                                             void (* func)(Item *, size_t))
{

    bool matchFound = false;

    Node * current = *ptr_head;

    for (size_t i = 0; current; i++)
    {
        if ((*ptr_item).rollNumber == current->item.rollNumber)
        {
            matchFound = true;
            (*func)(&(current->item), i);
        }
        current = current->next;
    }

    if (!(matchFound))
        printf("\nNo match found!\n");

}


void search_by_gpa_range_and_apply_function(Node ** ptr_head, double lower,
                                            double upper,
                                            void (* func)(Item *, size_t))
{

    bool matchFound = false;

    Node * current = *ptr_head;

    for (size_t i = 0; current; i++)
    {
        if ((lower < current->item.gpa) && (current->item.gpa < upper))
        {
            matchFound = true;
            (*func)(&(current->item), i);
        }
        current = current->next;
    }

    if (!(matchFound))
        printf("\nNo match found!\n");

}


void bubble_sort(Node ** ptr_head, bool rollNumber)
{

    if (*ptr_head == NULL)
    {
        printf("\nThe list is currently empty!\n");
        return;
    }

    Node * current;
    Node * previous;
    Node * next;

    Node * end_of_current_iteration = NULL;

    if (rollNumber)
    {
        while (end_of_current_iteration != (*ptr_head)->next)
        {
            current = *ptr_head;
            previous = NULL;
            next = (*ptr_head)->next;

            while (next != end_of_current_iteration)
            {
                if (current->item.rollNumber > next->item.rollNumber)
                {
                    if (previous == NULL)   // i.e. the zeroth and the first
                        *ptr_head = next;   // nodes are to be swapped.
                    else
                        previous->next = next;
                    current->next = next->next;
                    next->next = current;

                    // To swap the addresses stored in current and next.
                    current = next;
                    next = next->next;
                }

                previous = current;
                current = next;
                next = next->next;
            }

            end_of_current_iteration = current;
        }

        printf("\nSorted by Roll Number successfully!\n");
    }

    else
    {
       while (end_of_current_iteration != (*ptr_head)->next)
        {
            current = *ptr_head;
            previous = NULL;
            next = (*ptr_head)->next;

            while (next != end_of_current_iteration)
            {
                if (current->item.gpa > next->item.gpa)
                {
                    if (previous == NULL)   // i.e. the zeroth and the first
                        *ptr_head = next;   // nodes are to be swapped.
                    else
                        previous->next = next;
                    current->next = next->next;
                    next->next = current;

                    // To swap the addresses stored in current and next.
                    current = next;
                    next = next->next;
                }

                previous = current;
                current = next;
                next = next->next;
            }

            end_of_current_iteration = current;
        }

        printf("\nSorted by GPA successfully!\n");
    }

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
