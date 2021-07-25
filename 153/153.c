// C17 Standard

#include <stdio.h>


const char * messages[5] = { "    Thank you for the wonderful evening, ",
                             "You certainly prove that a ",
                             "is a special person. We must get together over ",
                             "a delicious ",
                             " and have a few laughs" };


struct name
{
    char first[20];
    char last[20];
};


struct person
{
    struct name nameOfThePerson;
    char favouriteFood[20];
    char job[20];
    double income;
};


int main(void)
{

    struct person dude = { { "Ewen", "Villard" },
                           "grilled salmon",
                           "computer programmer",
                           80000 };

    printf("Dear %s, \n\n", dude.nameOfThePerson.first);
    printf("%s%s.\n", messages[0], dude.nameOfThePerson.first);
    printf("%s%s\n", messages[1], dude.job);
    printf("%s\n", messages[2]);
    printf("%s%s%s.\n", messages[3], dude.favouriteFood, messages[4]);
    printf("\n%35s%s\n", " ", "See you soon,");
    printf("%35s%s\n", " ", "Shalala");

    return 0;

}





/* Trivia

 * Nested structures can also be used.

 */
