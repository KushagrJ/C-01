// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


char operatorStack[100];
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

        else // i.e. if infix[i] is an operator.
        {
            if (is_empty())
            {
                push(c);
            }

            else
            {
                while ((!is_empty()) && (precedence(peek()) >= precedence(c)))
                {
                    postfix[j++] = peek();
                    pop();
                }

                push(c);
            }
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
    index_of_top_item++;
    operatorStack[index_of_top_item] = c;
}


char peek(void)
{
    return operatorStack[index_of_top_item];
}


void pop(void)
{
    index_of_top_item--;
}


bool is_empty(void)
{
    if (index_of_top_item == -1)
        return true;
    else
        return false;
}


int precedence(char c)
{
    switch (c)
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





/* Trivia

 * Algorithm :-

   1. For (every character in the infix expression - from left to right)
          If (the scanned character is an operand)
              Add the scanned character to postfix.
          Else If (the scanned character is an opening parenthesis)
              Push the scanned character to operatorStack.
          Else If (the scanned character is a closing parenthesis)
              While (the top item of operatorStack is not an opening
              parenthesis)
                  Add the top item of operatorStack to postfix.
                  Pop the top item of operatorStack.
              Pop the opening parenthesis from operatorStack.
          Else If (the scanned character is an operator)
              If (operatorStack is empty)
                  Push the scanned character to operatorStack.
              Else
                  While (operatorStack is not empty) and (the precedence of the
                  top item of operatorStack is greater than or equal to the
                  precedence of the scanned character)
                      Add the top item of operatorStack to postfix.
                      Pop the top item of operatorStack.
                  Push the scanned character to operatorStack.
   2. While (operatorStack is not empty)
          Add the top item of operatorStack to postfix.
          Pop the top item of operatorStack.

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

 */
