// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include "123.h"


int main(void)
{

    puts("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
         "*                                                           *\n"
         "*   STUDENT LIST OF ROLL NUMBERS & GPAs                     *\n"
         "*                                                           *\n"
         "*                                                           *\n"
         "*   Choice   Operation                                      *\n"
         "*                                                           *\n"
         "*   1        Insert a new student's details into the list   *\n"
         "*                                                           *\n"
         "*   2        Display a student's details from the list      *\n"
         "*                                                           *\n"
         "*   3        Delete a student's details from the list       *\n"
         "*                                                           *\n"
         "*   4        Search the list by Roll Number                 *\n"
         "*                                                           *\n"
         "*   5        Search the list by GPA                         *\n"
         "*                                                           *\n"
         "*   6        Sort the list by Roll Number                   *\n"
         "*                                                           *\n"
         "*   7        Sort the list by GPA                           *\n"
         "*                                                           *\n"
         "*   8        Display the number of students in the list     *\n"
         "*                                                           *\n"
         "*   9        Exit                                           *\n"
         "*                                                           *\n"
         "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");


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
            scanf("%u", &temp_item.roll_number);

            printf("Enter their GPA: ");
            scanf("%lf", &temp_item.gpa);

            size_t position;
            while (true)
            {
                printf("Enter the position (0 to insert at the end): ");
                scanf("%zu", &position);
                if (position <= number_of_items_in_list(&students) + 1)
                    break;
                printf("Invalid position!\n");
            }

            insert_into_list_and_print(&students, &temp_item, position - 1);

            printf("\nStudent details inserted successfully!\n");
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
                while (true)
                {
                    printf("Enter the position (0 to print the entire list): ");
                    scanf("%zu", &position);
                    if (position <= number_of_items_in_list(&students))
                        break;
                    printf("Invalid position!\n");
                }

                print_from_list(&students, position - 1);
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
                while (true)
                {
                    printf("Enter the position: ");
                    scanf("%zu", &position);
                    if ((1 <= position) &&
                            (position <= number_of_items_in_list(&students)))
                        break;
                    printf("Invalid position!\n");
                }

                delete_from_list(&students, position - 1);

                printf("\nStudent details deleted successfully!\n");
            }
        }

        else if (choice == 4)
        {
            unsigned roll_number;

            printf("Enter the roll number: ");
            scanf("%u", &roll_number);

            bool match_found =
                search_list_by_roll_number_and_print(&students, roll_number);

            if (!(match_found))
                printf("\nNo match found!\n");
        }

        else if (choice == 5)
        {
            double lower, upper;

            printf("Enter the lower limit: ");
            scanf("%lf", &lower);

            printf("Enter the upper limit: ");
            scanf("%lf", &upper);

            bool match_found =
                search_list_by_gpa_range_and_print(&students, lower, upper);

            if (!(match_found))
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
                sort_list(&students, true);
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
                sort_list(&students, false);
                printf("\nSorted by GPA successfully!\n");
            }
        }

        else if (choice == 8)
        {
            printf("\nNo. of students: %zu\n",
                   number_of_items_in_list(&students));
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
   (1) Creating an empty list.
   (2) Inserting an item into a list 'at the end' / 'at any index'.
   (3) Printing 'all items' / 'an item at any index' from a list.
   (4) Deleting an item from a list at any index.
   (5) Searching by roll number in a list.
   (6) Searching by gpa range in a list.
   (7) Sorting a list by roll number / gpa.
   (8) Determining the number of items in a list.
   (9) Emptying a list.

 * A static array (not recommended because of a fixed number of items) and a
   dynamic array (using realloc()) can also be used to implement a list ADT.
 * Since a linked list is used, therefore there is no operation available to
   determine whether a list is full, as items can be added to the list as long
   as the computer doesn't run out of memory.

 * The declaration List students; should be thought of as a new variable
   students being declared of the type List.


 * In this program, const is avoided completely.
   Later, modify this program by using const wherever required.
   [See 111.c's Trivia (points (a), (b) and (c) to know what kind of problems
    might arise when using const in this program]

 * End of Trivia */
