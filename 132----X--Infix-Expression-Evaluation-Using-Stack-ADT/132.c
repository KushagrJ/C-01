// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>


char operator_stack[100];
int index_of_top_item_of_operator_stack = -1;

int operand_stack[100];
int index_of_top_item_of_operand_stack = -1;


void push_to_operator_stack(char);
char peek_operator_stack(void);
void pop_operator_stack(void);
bool is_operator_stack_empty(void);

void push_to_operand_stack(int);
int peek_operand_stack(void);
void pop_operand_stack(void);
bool is_operand_stack_empty(void);

int precedence(char);
int result(int, int, char);

// This function performs the repetitive steps described in Trivia.
void perform_operation(void);


int main(void)
{

    int c;

    printf("Enter an infix expression: ");

    while (((c = getchar()) != '\n') && (c != EOF))
    {
        if (isdigit(c))
        {
            push_to_operand_stack(c - '0');
        }

        else if (c == '(')
        {
            push_to_operator_stack('(');
        }

        else if (c == ')')
        {
            while (peek_operator_stack() != '(')
                perform_operation();

            pop_operator_stack();
        }

        else
        {
            while ((!is_operator_stack_empty()) &&
                       (precedence(peek_operator_stack()) >= precedence(c)))
            {
                perform_operation();
            }

            push_to_operator_stack(c);
        }
    }

    while (!is_operator_stack_empty())
        perform_operation();

    printf("The result is %d\n", operand_stack[0]);

    return 0;

}


void push_to_operator_stack(char c)
{
    (index_of_top_item_of_operator_stack)++;
    operator_stack[index_of_top_item_of_operator_stack] = c;
}


char peek_operator_stack(void)
{
    return operator_stack[index_of_top_item_of_operator_stack];
}


void pop_operator_stack(void)
{
    (index_of_top_item_of_operator_stack)--;
}


bool is_operator_stack_empty(void)
{
    if (index_of_top_item_of_operator_stack == -1)
        return true;
    else
        return false;
}


void push_to_operand_stack(int c)
{
    (index_of_top_item_of_operand_stack)++;
    operand_stack[index_of_top_item_of_operand_stack] = c;
}


int peek_operand_stack(void)
{
    return operand_stack[index_of_top_item_of_operand_stack];
}


void pop_operand_stack(void)
{
    (index_of_top_item_of_operand_stack)--;
}


bool is_operand_stack_empty(void)
{
    if (index_of_top_item_of_operand_stack == -1)
        return true;
    else
        return false;
}


int precedence(char operator)
{
    switch (operator)
    {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            fprintf(stderr, "Invalid expression!\n");
            exit(EXIT_FAILURE);
    }
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


void perform_operation(void)
{

    char operator = peek_operator_stack();
    pop_operator_stack();

    int operand_2 = peek_operand_stack();
    pop_operand_stack();

    int operand_1 = peek_operand_stack();
    pop_operand_stack();

    push_to_operand_stack(result(operand_1, operand_2, operator));

}





/* Trivia - 132.c

 * Algorithm :-

   1. For (every character in the infix expression - from left to right)
          1(a). If (the scanned character is an operand)
                    Push the scanned character to operand_stack.
          1(b). Else If (the scanned character is an opening parenthesis)
                    Push the opening parentheses to operator_stack.
          1(c). Else If (the scanned character is a closing parenthesis)
                    1. While (the top item of operator_stack is not an opening
                       parenthesis)
                         { 1. Save the top item of operator_stack in a variable
                         {    'operator'.
                         { 2. Pop operator_stack.
   Use a      <----------{ 3. Save the top item of operand_stack in a variable
   function              {    'operand_2'.
   for these             { 4. Pop operand_stack.
   repetitive            { 5. Save the top item of operand_stack in a variable
   steps.                {    'operand_1'.
                         { 6. Pop operand_stack.
                         { 7. Push the result of the operation to operand_stack.
                    2. Pop the opening parenthesis from operator_stack.
          1(d). Else If (the scanned character is an operator)
                    1. While (operator_stack is not empty) and (the precedence
                       of the top item of operator_stack is greater than or
                       equal to the precedence of the scanned character)
                         { 1. Save the top item of operator_stack in a variable
                         {    'operator'.
                         { 2. Pop operator_stack.
   Use a      <----------{ 3. Save the top item of operand_stack in a variable
   function              {    'operand_2'.
   for these             { 4. Pop operand_stack.
   repetitive            { 5. Save the top item of operand_stack in a variable
   steps.                {    'operand_1'.
                         { 6. Pop operand_stack.
                         { 7. Push the result of the operation to operand_stack.
                    2. Push the scanned character to operator_stack.
   2. While (operator_stack is not empty)
                         { 1. Save the top item of operator_stack in a variable
                         {    'operator'.
                         { 2. Pop operator_stack.
   Use a      <----------{ 3. Save the top item of operand_stack in a variable
   function              {    'operand_2'.
   for these             { 4. Pop operand_stack.
   repetitive            { 5. Save the top item of operand_stack in a variable
   steps.                {    'operand_1'.
                         { 6. Pop operand_stack.
                         { 7. Push the result of the operation to operand_stack.


 * This program focusses on the demonstration of the infix expression
   evaluation, and not on the stack ADT.
   Hence, the stacks are used as global variables and no bounds checking has
   been done - Bad programming practice.

 * End of Trivia */
