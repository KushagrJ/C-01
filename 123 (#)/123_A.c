// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include "123.h"


int main(void)
{

    printf("\n");
    puts("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
    puts("*                                                         *");
    puts("*   STUDENT LIST OF ROLL NUMBERS & GPAs                   *");
    puts("*                                                         *");
    puts("*                                                         *");
    puts("*   Choice   Operation                                    *");
    puts("*                                                         *");
    puts("*   1        Insert a new student's details in the list   *");
    puts("*                                                         *");
    puts("*   2        Display a student's details from the list    *");
    puts("*                                                         *");
    puts("*   3        Remove a student's details from the list     *");
    puts("*                                                         *");
    puts("*   4        Search the list by Roll Number               *");
    puts("*                                                         *");
    puts("*   5        Search the list by GPA                       *");
    puts("*                                                         *");
    puts("*   6        Sort the list by Roll Number                 *");
    puts("*                                                         *");
    puts("*   7        Sort the list by GPA                         *");
    puts("*                                                         *");
    puts("*   8        Display the number of students in the list   *");
    puts("*                                                         *");
    puts("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");


    List students = create_empty_list();
    Item temp;


    while (true)
    {
        unsigned choice;
        printf("\n\nEnter your choice: ");
        scanf("%u", &choice);

        if (choice == 1)
        {
            printf("\nEnter the student's roll number: ");
            scanf("%u", &temp.rollNumber);

            printf("Enter their GPA: ");
            scanf("%lf", &temp.gpa);

            size_t position;
            printf("Enter the position in the list (0 for last position): ");
            scanf("%zu", &position);

            size_t index_of_inserted_item =
                insert_item_in_list(&students, position - 1, &temp);

            printf("\nStudent details inserted successfully!\n");
            apply_function_to_item(&students, index_of_inserted_item,
                                   print_item);
        }

        else if (choice == 2)
        {
            size_t position;
            printf("Enter the position in the list (0 for entire list): ");
            scanf("%zu", &position);

            apply_function_to_item(&students, position - 1, print_item);
        }

        else if (choice == 3)
        {
            size_t position;
            printf("Enter the position in the list: ");
            scanf("%zu", &position);

            remove_item_from_list(&students, position - 1);

            printf("\nStudent details removed successfully!\n");
        }

        else if (choice == 4)
        {
            printf("Enter the roll number: ");
            scanf("%u", &temp.rollNumber);

            bool matchFound =
                search_by_rollNumber_and_apply_function(&students, &temp,
                                                        print_item);
            if (!(matchFound))
                printf("\nNo match found!\n");
        }

        else if (choice == 5)
        {
            double lower, upper;

            printf("Enter the lower limit: ");
            scanf("%lf", &lower);

            printf("Enter the upper limit: ");
            scanf("%lf", &upper);

            bool matchFound =
                search_by_gpa_range_and_apply_function(&students, lower, upper,
                                                       print_item);
            if (!(matchFound))
                printf("\nNo match found!\n");
        }

        else if (choice == 6)
        {
            bubble_sort(&students, true);

            printf("\nSorted by Roll Number successfully!\n");
        }

        else if (choice == 7)
        {
            bubble_sort(&students, false);

            printf("\nSorted by GPA successfully!\n");
        }

        else if (choice == 8)
        {
            printf("%zu\n", number_of_items_in_list(&students));
        }


        char resume;
        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &resume);

        if (resume != 'y')
            break;
    }


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
   (01) Creating an empty list.
   (02) Inserting an item at any index in a list.
   (03) Operating on 'all items' / 'an item at any index' in a list.
   (04) Removing an item at any index from a list.
   (05) Searching for an item by roll number in a list and operating on it.
   (06) Searching for an item by gpa range in a list and operating on it.
   (07) Sorting a list by roll number.
   (08) Sorting a list by gpa.
   (09) Determining how many items are there in a list.
   (10) Emptying a list.
 * The static array method (not recommended because of a fixed number of items)
   and the realloc() method can also be used to implement a list ADT.
   Since a linked list is used, therefore there is no operation added to
   determine whether the list is full, as elements can be added to this list
   as long as the computer doesn't run out of memory.

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
