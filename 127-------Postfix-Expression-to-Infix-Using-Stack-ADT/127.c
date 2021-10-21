// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


char stack[100][100];
int index_of_top_item = -1;


void push(char *);
char * peek(void);
void pop(void);
bool is_empty(void);


int main(void)
{

    int c;
    char temp1[100];
    char temp2[50];

    printf("Enter a postfix expression: ");

    while (((c = getchar()) != '\n') && (c != EOF))
    {
        if (isalnum(c))
        {
            push((char [2]) {c, '\0'});
        }

        else
        {
            temp1[0] = '(';

            strcpy(temp2, peek());
            pop();

            strcpy(temp1 + 1, peek());
            pop();

            strcat(temp1, (char [4]) {')', c, '(', '\0'});

            strcat(temp1, temp2);

            strcat(temp1, (char [2]) {')', '\0'});

            push(temp1);
        }
    }

    printf("The equivalent infix expression is %s\n", stack[0]);

    return 0;

}


void push(char * s)
{
    index_of_top_item++;
    strcpy(stack[index_of_top_item], s);
}


char * peek(void)
{
    return stack[index_of_top_item];
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





/* Trivia - 127.c

 * This program focusses on the demonstration of the postfix to infix expression
   conversion, and not on the stack ADT.
   Hence, the stack is used as a global variable and no bounds checking has been
   done - Bad programming practice.

 * End of Trivia */
