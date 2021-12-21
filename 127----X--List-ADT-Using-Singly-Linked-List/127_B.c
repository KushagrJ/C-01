#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "127.h"


void create_empty_list(Node** ptr_head)
{
    *ptr_head = NULL;
}


void insert_into_list_and_print(Node** ptr_head, Item* ptr_item, ssize_t index)
{

    Node* new = (Node*) malloc(sizeof (Node));
    if (new == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation!\n");
        exit(EXIT_FAILURE);
    }
    memmove(&(new->item), ptr_item, sizeof (Item));

    size_t index_where_inserted;

    if ((index == 0) || ((*ptr_head == NULL) && (index == -1)))
    {
        index_where_inserted = (size_t) 0;

        new->next = *ptr_head;
        *ptr_head = new;
    }

    else
    {
        Node* current = *ptr_head;
        index_where_inserted = (size_t) 1;

        if (index == -1)
        {
            while (current->next)
            {
                current = current->next;
                (index_where_inserted)++;
            }
        }

        else
        {
            while (index_where_inserted < (size_t) index)
            {
                current = current->next;
                (index_where_inserted)++;
            }
        }

        new->next = current->next;
        current->next = new;
    }

    printf("\nStudent No. %zu\n", index_where_inserted + 1);
    printf("Roll No.: %u\n", new->item.roll_number);
    printf("GPA: %.1f\n", new->item.gpa);

}


void print_from_list(Node** ptr_head, ssize_t index)
{

    Node* current = *ptr_head;

    if (index == -1)
    {
        for (size_t i = 0; current; i++)
        {
            printf("\nStudent No. %zu\n", i+1);
            printf("Roll No.: %u\n", current->item.roll_number);
            printf("GPA: %.1f\n", current->item.gpa);
            current = current->next;
        }
    }

    else
    {
        ssize_t i;
        for (i = 0; i < index; i++)
            current = current->next;
        printf("\nStudent No. %zu\n", i+1);
        printf("Roll No.: %u\n", current->item.roll_number);
        printf("GPA: %.1f\n", current->item.gpa);
    }

}


void delete_from_list(Node** ptr_head, size_t index)
{

    if (index == 0)
    {
        Node* temp = *ptr_head;
        *ptr_head = (*ptr_head)->next;
        free(temp);
    }

    else
    {
        Node* current = *ptr_head;

        for (size_t i = 1; i < index; i++)
            current = current->next;

        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }

}


bool search_list_by_roll_number_and_print(Node** ptr_head, unsigned roll_number)
{

    bool match_found = false;

    Node* current = *ptr_head;

    for (size_t i = 0; current; i++)
    {
        if (roll_number == current->item.roll_number)
        {
            match_found = true;
            printf("\nStudent No. %zu\n", i+1);
            printf("Roll No.: %u\n", current->item.roll_number);
            printf("GPA: %.1f\n", current->item.gpa);
        }

        current = current->next;
    }

    return match_found;

}


bool search_list_by_gpa_range_and_print(Node** ptr_head, double lower,
                                        double upper)
{

    bool match_found = false;

    Node* current = *ptr_head;

    for (size_t i = 0; current; i++)
    {
        if ((lower < current->item.gpa) && (current->item.gpa < upper))
        {
            match_found = true;
            printf("\nStudent No. %zu\n", i+1);
            printf("Roll No.: %u\n", current->item.roll_number);
            printf("GPA: %.1f\n", current->item.gpa);
        }

        current = current->next;
    }

    return match_found;

}


void sort_list(Node** ptr_head, bool sort_list_by_roll_number)
{

    Node* current;
    Node* previous;
    Node* next;

    Node* end_of_current_iteration = NULL;

    if (sort_list_by_roll_number)
    {
        while (end_of_current_iteration != (*ptr_head)->next)
        {
            current = *ptr_head;
            previous = NULL;
            next = (*ptr_head)->next;

            while (next != end_of_current_iteration)
            {
                if (current->item.roll_number > next->item.roll_number)
                {
                    if (previous == NULL)
                        *ptr_head = next;
                    else
                        previous->next = next;
                    current->next = next->next;
                    next->next = current;

                    current = next;
                    next = next->next;
                }

                previous = current;
                current = next;
                next = next->next;
            }

            end_of_current_iteration = current;
        }
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
                    if (previous == NULL)
                        *ptr_head = next;
                    else
                        previous->next = next;
                    current->next = next->next;
                    next->next = current;

                    current = next;
                    next = next->next;
                }

                previous = current;
                current = next;
                next = next->next;
            }

            end_of_current_iteration = current;
        }
    }

}


size_t number_of_items_in_list(Node** ptr_head)
{

    Node* current = *ptr_head;

    size_t i;

    for (i = (size_t) 0; current; i++)
        current = current->next;

    return i;

}


void empty_list(Node** ptr_head)
{

    Node* current = *ptr_head;

    while (current)
    {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

}
