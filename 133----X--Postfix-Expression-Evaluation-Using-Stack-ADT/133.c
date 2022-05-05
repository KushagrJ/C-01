// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>


int operand_stack[100];
int index_of_top_item = -1;


void push(int);
int peek(void);
void pop(void);
bool is_empty(void);

int result(int, int, char);


int main(void)
{

    int c;

    printf("Enter a postfix expression: ");

    while (((c = getchar()) != '\n') && (c != EOF))
    {
        if (isdigit(c))
        {
            push(c - '0');
        }

        else
        {
            int operand_2 = peek();
            pop();

            int operand_1 = peek();
            pop();

            push(result(operand_1, operand_2, c));
        }
    }

    printf("The result is %d\n", peek());

    return 0;

}


void push(int c)
{
    (index_of_top_item)++;
    operand_stack[index_of_top_item] = c;
}


int peek(void)
{
    return operand_stack[index_of_top_item];
}


void pop(void)
{
    (index_of_top_item)--;
}


bool is_empty(void)
{
    if (index_of_top_item == -1)
        return true;
    else
        return false;
}


int result(int operand_1, int operand_2, char operator)
{
    switch (operator)
    {
        case '+':
            return operand_1 + operand_2;
        case '-':
            return operand_1 - operand_2;
        case '*':
            return operand_1 * operand_2;
        case '/':
            return operand_1 / operand_2;
        case '^':
            return (int) pow(operand_1, operand_2);
        default:
            fprintf(stderr, "Invalid expression!\n");
            exit(EXIT_FAILURE);
    }
}





/* Trivia - 133.c

 * This program focusses on the demonstration of the postfix expression
   evaluation, and not on the stack ADT.
   Hence, the stack is used as a global variable and no bounds checking has been
   done - Bad programming practice.

 * End of Trivia */
