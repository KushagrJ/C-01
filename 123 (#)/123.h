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

// To hide the fact in the prototypes and main() that a linked list is used.
typedef Node * List;


void print_item(Item *);

List create_empty_list(void);

_Bool list_is_empty(List *);

size_t number_of_items_in_list(List *);

// If index is -1, then the function will be applied to all items sequentially.
// Else, the function will be applied to the item at the given index.
void apply_function_to_item(List *, ssize_t index, void (*)(Item *));

// If index is -1, then the item will be inserted at the end of the list.
// Else, the item will be inserted at the given index.
void insert_item_in_list(List *, ssize_t index, Item *);

void remove_item_from_list(List *, size_t index);

void replace_item_in_list(List *, size_t index, Item *);

size_t search_for_item_in_list(List *, Item *);

void empty_list(List *);
