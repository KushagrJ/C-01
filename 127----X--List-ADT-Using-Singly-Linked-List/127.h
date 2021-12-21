#include <sys/types.h>
#include <stdbool.h>


struct student_roll_number_and_gpa
{
    unsigned roll_number;
    double gpa;
};

typedef struct student_roll_number_and_gpa Item;


struct node
{
    Item item;
    struct node* next;
};

typedef struct node Node;

// To hide the exact implementation details from the main() function.
typedef Node* List;


// Argument 1: Address of a List variable.
void create_empty_list(Node**);

// Argument 1: Address of a List variable.
// Argument 2: Address of the item which is to be inserted.
// Argument 3: Index where the item is to be inserted.
// If the index is -1, then the item will be inserted at the end.
// Else, the item will be inserted at the given index.
// Note: The item will be printed in the following manner :-
//       Student No. 1
//       Roll No.: 22
//       GPA: 10.0
// (the student number is the same as the position in the list, i.e. index + 1)
void insert_into_list_and_print(Node**, Item*, ssize_t);

// Argument 1: Address of a List variable.
// Argument 2: Index of the item which is to be printed.
// If the index is -1, then all items will be printed sequentially.
// Else, the item at the given index will be printed.
// Note: The items will be printed in the following manner :-
//       Student No. 1
//       Roll No.: 22
//       GPA: 10.0
// (the student number is the same as the position in the list, i.e. index + 1)
void print_from_list(Node**, ssize_t);

// Argument 1: Address of a List variable.
// Argument 2: Index of the item which is to be deleted.
void delete_from_list(Node**, size_t);

// Argument 1: Address of a List variable.
// Argument 2: Roll number which is to be searched.
// Return Value: Bool value depicting whether matches were found.
// Note: All matched items will be printed in the following manner :-
//       Student No. 1
//       Roll No.: 22
//       GPA: 10.0
// (the student number is the same as the position in the list, i.e. index + 1)
bool search_list_by_roll_number_and_print(Node**, unsigned);

// Argument 1: Address of a List variable.
// Argument 2: Lower limit of the gpa range which is to be searched.
// Argument 3: Upper limit of the gpa range which is to be searched.
// Return Value: Bool value depicting whether matches were found.
// Note: All matched items will be printed in the following manner :-
//       Student No. 1
//       Roll No.: 22
//       GPA: 10.0
// (the student number is the same as the position in the list, i.e. index + 1)
bool search_list_by_gpa_range_and_print(Node**, double, double);

// Argument 1: Address of a List variable.
// Argument 2: Bool value depicting whether the list is to be sorted by
//             roll_number or by gpa.
// If the bool value is true, then the list will be sorted by roll_number.
// Else, the list will be sorted by gpa.
void sort_list(Node**, bool);

// Argument 1: Address of a List variable.
// Return Value: Number of items in the list.
size_t number_of_items_in_list(Node**);

// Argument 1: Address of a List variable.
void empty_list(Node**);
