// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include "123.h"


int main(void)
{

    puts("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
         "*                                                         *\n"
         "*   STUDENT LIST OF ROLL NUMBERS & GPAs                   *\n"
         "*                                                         *\n"
         "*                                                         *\n"
         "*   Choice   Operation                                    *\n"
         "*                                                         *\n"
         "*   1        Insert a new student's details in the list   *\n"
         "*                                                         *\n"
         "*   2        Display a student's details from the list    *\n"
         "*                                                         *\n"
         "*   3        Remove a student's details from the list     *\n"
         "*                                                         *\n"
         "*   4        Search the list by Roll Number               *\n"
         "*                                                         *\n"
         "*   5        Search the list by GPA                       *\n"
         "*                                                         *\n"
         "*   6        Sort the list by Roll Number                 *\n"
         "*                                                         *\n"
         "*   7        Sort the list by GPA                         *\n"
         "*                                                         *\n"
         "*   8        Display the number of students in the list   *\n"
         "*                                                         *\n"
         "*   9        Exit                                         *\n"
         "*                                                         *\n"
         "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");


    List students;
    create_empty_list(&students);
    Item temp_item;


    while (true)
    {
        unsigned choice;
        printf("\n\nEnter your choice: ");
        scanf("%u", &choice);

        if (choice == 1)
        {
            printf("\nEnter the student's roll number: ");
            scanf("%u", &temp_item.rollNumber);

            printf("Enter their GPA: ");
            scanf("%lf", &temp_item.gpa);

            size_t position;
            printf("Enter the position in the list (0 for last position): ");
            scanf("%zu", &position);

            size_t index_of_inserted_item =
                insert_item_in_list(&students, &temp_item, position - 1);

            printf("\nStudent details inserted successfully!\n");

            apply_function_to_item(&students, index_of_inserted_item,
                                   print_item);
        }

        else if (choice == 2)
        {
            if (number_of_items_in_list(&students) == 0)
            {
                printf("\nThe list is currently empty!\n");
            }

            else
            {
                size_t position;
                printf("Enter the position in the list (0 for entire list): ");
                scanf("%zu", &position);

                apply_function_to_item(&students, position - 1, print_item);
            }
        }

        else if (choice == 3)
        {
            if (number_of_items_in_list(&students) == 0)
            {
                printf("\nThe list is currently empty!\n");
            }

            else
            {
                size_t position;
                printf("Enter the position in the list: ");
                scanf("%zu", &position);

                remove_item_from_list(&students, position - 1);

                printf("\nStudent details removed successfully!\n");
            }
        }

        else if (choice == 4)
        {
            unsigned rollNumber;

            printf("Enter the roll number: ");
            scanf("%u", &rollNumber);

            bool matchFound =
                search_by_rollNumber_and_apply_function(&students, rollNumber,
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
            if (number_of_items_in_list(&students) == 0)
            {
                printf("\nThe list is currently empty!\n");
            }

            else
            {
                bubble_sort(&students, true);
                printf("\nSorted by Roll Number successfully!\n");
            }
        }

        else if (choice == 7)
        {
            if (number_of_items_in_list(&students) == 0)
            {
                printf("\nThe list is currently empty!\n");
            }

            else
            {
                bubble_sort(&students, false);
                printf("\nSorted by GPA successfully!\n");
            }
        }

        else if (choice == 8)
        {
            printf("%zu\n", number_of_items_in_list(&students));
        }

        else if (choice == 9)
        {
            break;
        }
    }


    empty_list(&students);

    return 0;

}





/* Trivia - 123_A.c

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


 * In this program, a list ADT is implemented using a singly linked list which
   can contain a variable number of items.
   Each item consists of the roll number and GPA of a student.

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

 * A static array (not recommended because of a fixed number of items) and a
   dynamic array (using realloc()) can also be used to implement a list ADT.
 * Since a linked list is used, therefore there is no operation available to
   determine whether a list is full, as items can be added to the list as long
   as the computer doesn't run out of memory.

 * The declaration List students; should be thought of as a new variable
   students being declared of the type List.


 * In this program, const is avoided completely.
   Later, modify this program by using const wherever required.
   [See 111.c's Trivia (points (a), (b) and (c)]

 * End of Trivia */
