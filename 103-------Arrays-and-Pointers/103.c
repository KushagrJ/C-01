// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>


int sum(int, int, const int (*)[*]);
// or int sum(int, int, const int [][*]);
// or int sum(int, int, const int [*][*]);
// or int sum(int rows, int cols, const int (* arr)[cols]);
// or int sum(int rows, int cols, const int arr[][cols]);
// or int sum(int rows, int cols, const int arr[rows][cols]);


int main(void)
{

    int rows, cols;
    printf("Enter the number of rows: "); scanf("%d", &rows);
    printf("Enter the number of columns: "); scanf("%d", &cols);
    printf("\n");

    // A variable-length 2-D array.
    int arr[rows][cols];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("Enter the integer at row no. %d & column no. %d: ", i, j);
            scanf("%d", &arr[i][j]);
        }
        printf("\n");
    }

    printf("The sum of all integers = %d\n", sum(rows, cols, arr));

    return 0;

}


int sum(int rows, int cols, const int (* arr)[cols])
// or int sum(int rows, int cols, const int arr[][cols])
// or int sum(int rows, int cols, const int arr[rows][cols])
{

    int sum = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            sum += arr[i][j];

    return sum;

}





/* Trivia - 103.c

 * int sum(const int (* arr)[cols], int rows, int cols) is invalid, since the
   arr declaration uses rows and cols and thus, they have to be declared before
   arr in the parameter list.
 * In int sum(int, int, const int (*)[*]), the asterisk inside the brackets,
   i.e. [*], is simply a placeholder for dimensions in variable-length arrays.
   It is not related to pointers in any way.

 * End of Trivia */
