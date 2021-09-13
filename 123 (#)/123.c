// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


struct student_rollNumber_and_gpa
{
    unsigned rollNumber;
    double gpa;
};

typedef struct student_rollNumber_and_gpa Item;


struct node
{
    Item item;
    struct node * next;
};

typedef struct node Node;

typedef Node * List; // To hide the fact that a linked list is used.


void print_item(const Item *);

void create_empty_list(List *);
_Bool list_is_empty(const List *);
size_t number_of_items_in_list(const List *);
void apply_function_to_item(List *, ssize_t, void (*)(const Item *));
void add_item_to_list(List *, ssize_t, const Item *);
void remove_item_from_list(List *, size_t);
void replace_item_in_list(List *, size_t, Item *);
size_t search_for_item_in_list(List *, Item *);
void empty_list(List *);


int main(void)
{

    List students;
    create_empty_list(&students);

    Item temp_item;


    temp_item.rollNumber = 0;
    temp_item.gpa = 9.0;
    add_item_to_list(&students, -1, &temp_item);

    temp_item.rollNumber = 1;
    temp_item.gpa = 9.1;
    add_item_to_list(&students, -1, &temp_item);

    temp_item.rollNumber = 2;
    temp_item.gpa = 9.2;
    add_item_to_list(&students, -1, &temp_item);

    apply_function_to_item(&students, -1, print_item);
    printf("\n\n");


    temp_item.rollNumber = 3;
    temp_item.gpa = 9.3;
    add_item_to_list(&students, 1, &temp_item);

    apply_function_to_item(&students, -1, print_item);
    printf("\n\n");


    empty_list(&students);

    return 0;

}


void print_item(const Item * ptr_item)
{
    printf("Roll No. - %u\n", ptr_item->rollNumber);
    printf("GPA - %.1f/10\n", ptr_item->gpa);
}


void create_empty_list(List * ptr_List_variable)
{
    *ptr_List_variable = NULL;
}


_Bool list_is_empty(const List * ptr_List_variable)
{
    if (*ptr_List_variable == NULL)
        return 1;
    else
        return 0;
}


size_t number_of_items_in_list(const List * ptr_List_variable)
{

    Node * current = *ptr_List_variable;
    // or List current = *ptr_List_variable; (Node * makes more sense here).

    size_t i = 0;
    while (current)
    {
        current = current->next;
        i++;
    }

    return i;

}


void apply_function_to_item(List * ptr_List_variable, ssize_t index,
                            void (* func)(const Item *))
// Use only a valid index.
{

    Node * current = *ptr_List_variable;
    // or List current = *ptr_List_variable; (Node * makes more sense here).

    if (index == -1) // Apply function to all items.
    {
        while (current)
        {
            (*func)(&(current->item));
            current = current->next;
        }
    }

    else // Apply function to item at index.
    {
        for (size_t i = 0; i != (size_t) index; i++)
            current = current->next;
        (*func)(&(current->item));
    }

}


void add_item_to_list(List * ptr_List_variable, ssize_t index,
                      const Item * ptr_item)
// Use only a valid index.
{

    Node * current = *ptr_List_variable;
    // or List current = *ptr_List_variable; (Node * makes more sense here).
    Node * previous = NULL;
    // or List previous = NULL; (Node * makes more sense here).

    if (index == -1) // Add item at the end.
    {
        while (current)
        {
            previous = current;
            current = current->next;
        }
    }

    else // Add item at index.
    {
        for (size_t i = 0; i != (size_t) index; i++)
        {
            previous = current;
            current = current->next;
        }
    }

    Node * new = (Node *) malloc(sizeof (Node));
    // or List new = (List) malloc(...); (Node * makes more sense here).
    if (new == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation!\n");
        exit(EXIT_FAILURE);
    }
    memmove(&(new->item), ptr_item, sizeof (Item));

    if (previous == NULL) // i.e. new points to the first node.
        *ptr_List_variable = new;
    else
        previous->next = new;
    new->next = current;

}


void empty_list(List * ptr_List_variable)
{

    Node * current = *ptr_List_variable;
    // or List current = *ptr_List_variable; (Node * makes more sense here).

    while (current)
    {
        Node * next = current->next;
        free(current);
        current = next;
    }

}





/* Trivia

 * A type specifies two kinds of information: a set of properties and a set of
   operations.
   For eg., the int type's property is that it represents an integer value
   (within the storage limits) and the allowed operations include changing the
   sign of an int value, adding two int values, etc.

 * Defining a new type involves three steps :-
   (1) Providing an abstract desciption of the type's properties and of the
       operations that can be performed on the type.
       This description shouldn't be tied to any particular implementation or
       programming language.
       Such a formal abstract description is called an abstract data type (ADT).
   (2) Developing a programming interface that implements the ADT, i.e.
       indicating how to store the data and describing a set of functions to be
       used on the ADT, specific to an implementation or a programming language.
       The interface should parallel the ADT description as closely as possible.
   (3) Writing code to implement the interface in the specific implementation
       or the programming language


 * In this program, a list ADT is implemented using a linked list which consists
   of items. Each item in turn consists of the roll number and GPA of a student.
 * The following operations can be performed on such a list :-
   (1) Creating an empty list.
   (2) Determining whether a list is empty.
   (3) Determining how many items are there in a list.
   (4) Operating on 'all items' / 'an item at any index' in a list.
   (5) Inserting an item at any index in a list.
   (6) Removing an item at any index from a list.
   (7) Replacing an item at any index in a list with another item.
   (8) Searching for an item in a list and determining the index of its first
       occurrence.
   (9) Emptying a list.

 * The declaration List students; should be thought of as a new variable
   students being declared of the type List.

 */
