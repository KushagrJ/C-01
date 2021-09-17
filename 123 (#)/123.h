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
    struct node * next;
};

typedef struct node Node;

// To hide the fact in the prototypes and main() that a linked list is used.
typedef Node * List;


void print_item(Item *, size_t);

List create_empty_list(void);

// If index is -1, then the item will be inserted at the end of the list.
// Else, the item will be inserted at the given index.
size_t insert_item_in_list(List *, ssize_t index, Item *);

// If index is -1, then the function will be applied to all items sequentially.
// Else, the function will be applied to the item at the given index.
void apply_function_to_item(List *, ssize_t index, void (*)(Item *, size_t));

void remove_item_from_list(List *, size_t index);

bool search_by_rollNumber_and_apply_function(List *, Item *,
                                             void (*)(Item *, size_t));

bool search_by_gpa_range_and_apply_function(List *, double, double,
                                            void (*)(Item *, size_t));

// If rollNumber is true, then the list will be sorted by rollNumber.
// Else, the list will be sorted by gpa.
void bubble_sort(List *, bool rollNumber);

size_t number_of_items_in_list(List *);

void empty_list(List *);
