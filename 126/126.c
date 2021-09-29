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

    char infix[100];
    printf("Enter an infix expression: ");
    scanf(" %99[^\n]", infix);

    char postfix[100];

    int j = 0;

    for (int i = 0; infix[i]; i++)
    {
        if (isalnum(infix[i])) // i.e. if infix[i] is an operand.
        {
            postfix[j++] = infix[i];
        }

        else if (infix[i] == '(')
        {
            push('(');
        }

        else if (infix[i] == ')')
        {
            while (true)
            {
                char temp = peek();
                pop();
                if (temp == '(')
                    break;
                postfix[j++] = temp;
            }
        }

        else // i.e. if infix[i] is an operator.
        {
            if (is_empty())
            {
                push(infix[i]);
            }

            else
            {
                while ((!is_empty()) &&
                           (precedence(peek()) >= precedence(infix[i])))
                {
                    postfix[j++] = peek();
                    pop();
                }

                push(infix[i]);
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

 * Study other algorithms as well that give different orders of evaluation due
   to different associativities of operators.
 * In this program, the condition precedence(peek()) > precedence(infix[i])
   makes the associativity of all operators right-to-left, whereas the condition
   precedence(peek()) >= precedence(infix[i]) makes the associativity of all
   operators left-to-right.

 * This program focusses on the demonstration of the infix to postfix expression
   conversion, and not on the stack ADT.
   Hence, the stack is used as a global variable and no bounds checking has been
   done - Bad programming practice.


 * For eg., A+B*C/(D+E) [Assuming left-to-right associativity]

   Token    Action         Postfix    Stack    Notes

   A        Add A          A
   +        Push +         A              +    stack is empty
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
