// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>


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

typedef Node * List;


int main(void)
{

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
       or the programming language


 * In this program, a list ADT is implemented using a linked list which consists
   of items. Each item in turn consists of the roll number and GPA of a student.
 * The following operations can be performed on such a list :-
   (1) Creating an empty list.
   (2) Determining whether a list is empty.
   (3) Determining how many items are there in a list.
   (4) Accessing an item at any position in a list.
   (5) Inserting an item at any position in a list.
   (6) Removing an item at any position from a non-empty list.
   (7) Replacing an item at any position in a list with another item.
   (8) Searching for an item in a list and determining its position.

 * The declaration List_of_items students; should be thought of as a new
   variable students being declared of the type List.

 */
