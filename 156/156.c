// C17 Standard
// Include input validation in version B of this program.

#include <stdio.h>
#include <stdlib.h>


struct marksOfTheStudent
{
    double mathematics;
    double programming;
    double algorithms;
    double average;
};

struct student
{
    char name[20];
    struct marksOfTheStudent marks;
};


void sort_pointers_to_structures(const struct student **);


int main(void)
{

    printf("Enter the details of 5 students :-\n\n");
    printf("%-18s %-18s %-18s %-18s\n\n", "Name", "Mathematics",
                                          "Programming", "Algorithms");

    struct student * students =
        (struct student *) malloc(5 * sizeof(struct student));

    for (int i = 0; i < 5; i++)
    {
        fgets(students[i].name, 20, stdin);
        scanf("%lf", &students[i].marks.mathematics);
        scanf("%lf", &students[i].marks.programming);
        scanf("%lf", &students[i].marks.algorithms);
        getchar();
    }

    for (int i = 0; i < 5; i++)
        students[i].marks.average =
            (students[i].marks.mathematics + students[i].marks.programming +
             students[i].marks.algorithms) / 3;

    const struct student * p[5];
    for (int i = 0; i < 5; i++)
        p[i] = &students[i];

    sort_pointers_to_structures(p);

    printf("\n\nAfter sorting according to average marks :-\n\n");
    printf("%-18s %-18s %-18s %-18s\n\n", "Name", "Mathematics",
                                          "Programming", "Algorithms");

    for (int i = 0; i < 5; i++)
        printf("%-18s %-18g %-18g %-18g\n", p[i]->name,
                                            p[i]->marks.mathematics,
                                            p[i]->marks.programming,
                                            p[i]->marks.algorithms);

    free(students);

    return 0;

}


void sort_pointers_to_structures(const struct student ** p)
{

    const struct student * temp;

    for (int i = 1; i < 5; i++)
        for (int j = 0; j < 5-i; j++)
            if (p[j]->marks.average < p[j+1]->marks.average)
                temp = p[j], p[j] = p[j+1], p[j+1] = temp;

}





/* Trivia

 * Pointers to structures are generally used as function arguments for reasons
   of efficiency, using const when needed to protect data from unintended
   changes.
   Passing structures by value is most often done for structures that are small
   to begin with, or by passing only the required members of large structures
   individually.

 */
