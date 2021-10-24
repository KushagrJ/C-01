// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


char operator_stack[100];
int index_of_top_item = -1;


void push(char);
char peek(void);
void pop(void);
bool is_empty(void);
int precedence(char);


int main(void)
{

    char postfix[100];

    int c;
    int j = 0;

    printf("Enter an infix expression: ");

    while (((c = getchar()) != '\n') && (c != EOF))
    {
        if (isalnum(c)) // i.e. if c is an operand.
        {
            postfix[j++] = c;
        }

        else if (c == '(')
        {
            push('(');
        }

        else if (c == ')')
        {
            while (peek() != '(')
            {
                postfix[j++] = peek();
                pop();
            }

            pop();
        }

        else // i.e. if c is an operator.
        {
            while ((!is_empty()) && (precedence(peek()) >= precedence(c)))
            {
                postfix[j++] = peek();
                pop();
            }

            push(c);
        }
    }

    while (!is_empty())
    {
        postfix[j++] = peek();
        pop();
    }

    postfix[j] = '\0';

    printf("The equivalent postfix expression is %s\n", postfix);

    return 0;

}


void push(char c)
{
    (index_of_top_item)++;
    operator_stack[index_of_top_item] = c;
}


char peek(void)
{
    return operator_stack[index_of_top_item];
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





/* Trivia - 126.c

 * Algorithm :-

   1. For (every character in the infix expression - from left to right)
          1(a). If (the scanned character is an operand)
                    Add the scanned character to postfix.
          1(b). Else If (the scanned character is an opening parenthesis)
                    Push the opening parenthesis to operator_stack.
          1(c). Else If (the scanned character is a closing parenthesis)
                    1. While (the top item of operator_stack is not an opening
                       parenthesis)
                           1. Add the top item of operator_stack to postfix.
                           2. Pop the top item of operator_stack.
                    2. Pop the opening parenthesis from operator_stack.
          1(d). Else If (the scanned character is an operator)
                    1. While (operator_stack is not empty) and (the precedence
                       of the top item of operator_stack is greater than or
                       equal to the precedence of the scanned character)
                           1. Add the top item of operator_stack to postfix.
                           2. Pop the top item of operator_stack.
                    2. Push the scanned character to operator_stack.
   2. While (operator_stack is not empty)
          1. Add the top item of operator_stack to postfix.
          2. Pop the top item of operator_stack.

 * In this algorithm, the condition precedence(peek()) > precedence(c) makes the
   associativity & the order of evaluation of the operators having the same
   precedence strictly right-to-left, whereas the condition
   precedence(peek()) >= precedence(c) makes the associativity & the order of
   evaluation of the operators having the same precedence strictly
   left-to-right.


 * This program focusses on the demonstration of the infix to postfix expression
   conversion, and not on the stack ADT.
   Hence, the stack is used as a global variable and no bounds checking has been
   done - Bad programming practice.


 * For eg., A+B*C/(D+E) [Assuming left-to-right associativity]

   Token    Action         Postfix    Stack    Notes (for precedence)

   A        Add A          A
   +        Push +         A              +
   B        Add B          AB             +
   *        Push *         AB            *+    prec. of + >= prec. of * is False
   C        Add C          ABC           *+
   /        Add & Pop *    ABC*           +    prec. of * >= prec. of / is True
            Push /         ABC*          /+    prec. of + >= prec. of / is False
   (        Push (         ABC*         (/+
   D        Add D          ABC*D        (/+
   +        Push +         ABC*D       +(/+    prec. of ( >= prec. of + is False
   E        Add E          ABC*DE      +(/+
   )        Add & Pop +    ABC*DE+      (/+
            Pop (          ABC*DE+       /+

            Add & Pop /    ABC*DE+/       +
            Add & Pop +    ABC*DE+/+

 * End of Trivia */
