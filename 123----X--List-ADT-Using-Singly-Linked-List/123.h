#include <sys/types.h>
#include <stdbool.h>


struct student_rollNumber_and_gpa
{
    unsigned rollNumber;
    double gpa;
};

typedef struct student_rollNumber_and_gpa Item;


struct node
{
    Item item;
    struct node* next;
};

typedef struct node Node;

// To hide the exact implementation details from the main() function.
typedef Node* List;


// Argument 1: Address of the item which is to be printed.
// Argument 2: Index of the item which is to be printed.
void print_item(Item*, size_t);

// Argument 1: Address of a List variable.
void create_empty_list(Node**);

// Argument 1: Address of a List variable.
// Argument 2: Address of the item which is to be inserted.
// Argument 3: Index where the item is to be inserted.
// Return Value: Index of the inserted item.
// If the index is -1, then the item will be inserted at the end of the list.
// Else, the item will be inserted at the given index.
size_t insert_item_in_list(Node**, Item*, ssize_t);

// Argument 1: Address of a List variable.
// Argument 2: Index of the item on which the function is to be applied.
// Argument 3: Address of the function which is to be applied to the item.
// If the index is -1, then the function will be applied to all items sequentially.
// Else, the function will be applied to the item at the given index.
void apply_function_to_item(Node**, ssize_t index, void (*)(Item*, size_t));

// Argument 1: Address of a List variable.
// Argument 2: Index of the item which is to be removed.
void remove_item_from_list(Node**, size_t index);

// Argument 1: Address of a List variable.
// Argument 2: rollNumber which is to be searched.
// Argument 3: Address of the function which is to be to be applied to the
//             matched item(s).
// Return Value: Bool value depicting whether matches were found.
bool search_by_rollNumber_and_apply_function(Node**, unsigned,
                                             void (*)(Item*, size_t));

// Argument 1: Address of a List variable.
// Argument 2: Lower limit of the gpa range which is to be searched.
// Argument 3: Upper limit of the gpa range which is to be searched.
// Argument 4: Address of the function which is to be to be applied to the
//             matched item(s).
// Return Value: Bool value depicting whether matches were found.
bool search_by_gpa_range_and_apply_function(Node**, double, double,
                                            void (*)(Item*, size_t));

// Argument 1: Address of a List variable.
// Argument 2: Bool value depicting whether the list is to be sorted by
//             rollNumber or by gpa.
// If the bool value is true, then the list will be sorted by rollNumber.
// Else, the list will be sorted by gpa.
void bubble_sort(Node**, bool);

// Argument 1: Address of a List variable.
// Return Value: Number of items in the list.
size_t number_of_items_in_list(Node**);

// Argument 1: Address of a List variable.
void empty_list(Node**);
