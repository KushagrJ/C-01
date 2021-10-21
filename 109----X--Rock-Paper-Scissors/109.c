// C17 Standard
// This program doesn't include input validation.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{

    srand((unsigned) time(NULL));

    printf("Player 1 (User) vs. Player 2 (Computer)\n");
    printf("0 = Rock; 1 = Paper; 2 = Scissors\n\n");

    int p1_choice;
    printf("Player 1, enter your choice: ");
    scanf("%d", &p1_choice);

    printf("\nPlayer 1: ");
    switch (p1_choice) { case 0: printf("Rock\n"); break;
                         case 1: printf("Paper\n"); break;
                         case 2: printf("Scissors\n"); }

    // To generate random integers among 0, 1 and 2.
    int p2_choice = (rand() % 3);

    printf("Player 2: ");
    switch (p2_choice) { case 0: printf("Rock\n\n"); break;
                         case 1: printf("Paper\n\n"); break;
                         case 2: printf("Scissors\n\n"); }

    // a % b in Python is equivalent to ((a % b) + b) % b in C.
    int winner = (((p1_choice - p2_choice) % 3) + 3) % 3;

    if (p1_choice == p2_choice)
        printf("Draw!\n");
    else
        printf("Player %d wins!\n", winner);

    return 0;

}





/* Trivia - 109.c

 * The rand() function, prototyped in stdlib.h, returns pseudo-random integers
   between 0 and RAND_MAX (defined in the standard library), which means that
   the numbers are generated based on a given algorithm.
   Generating real randomness is very hard for a computer, but for practical,
   non-cryptographic purposes, an algorithm that tries to evenly distribute
   the generated sequences works fine.
 * The starting point of the algorithm used by rand() is called the seed.
   If the seed for rand() is not changed, then rand() will generate the same
   sequence of numbers every time.
   The default seed of rand() is 1.
 * The srand() function, also prototyped in stdlib.h, is used to set the seed
   for rand() in a program. So, srand() should only be called once in a program.
   In order to make rand() use a different seed every time it's called, the
   argument of srand() should be a value that is constantly changing, such as
   the current time.

 * End of Trivia */
