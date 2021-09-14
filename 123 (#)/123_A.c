// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include "123.h"


int main(void)
{

    List students = create_empty_list();

    Item temp_item;


    temp_item.rollNumber = 0;
    temp_item.gpa = 9.0;
    insert_item_in_list(&students, -1, &temp_item);

    temp_item.rollNumber = 1;
    temp_item.gpa = 9.1;
    insert_item_in_list(&students, -1, &temp_item);

    temp_item.rollNumber = 2;
    temp_item.gpa = 9.2;
    insert_item_in_list(&students, -1, &temp_item);

    apply_function_to_item(&students, -1, print_item);
    printf("\n\n");


    temp_item.rollNumber = 3;
    temp_item.gpa = 9.3;
    insert_item_in_list(&students, 1, &temp_item);

    apply_function_to_item(&students, -1, print_item);
    printf("\n\n");


    empty_list(&students);

    return 0;

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
       or the programming language.


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

 * Using const List * parameters for functions that don't change the list is
   confusing in this program.
   List is equivalent to Node *, so const List * actually means Node * const *,
   and not const Node **.
   This means that using a const List * parameter, the contents of the items can
   still be altered.
   Thus, a const List * parameter such as const List * ptr_head only means that
   head cannot be made to point to another structure.
   So, using const List * just to show that head (i.e. the List variable) will
   not point to any other structure is confusing, as the exact implementation
   details are supposed to be hidden at the higher level and this type can
   make the user incorrectly believe that the contents of the items will not be
   altered by the function.
   To make the functions truly unable to change the contents of the items, a
   parameter of type const Node * const * needs to be used.
   Hence, in this program, const is avoided completely.

 */
