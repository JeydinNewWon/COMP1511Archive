// A program to print out the sum of students and tutors in the class.
// By Jayden Nguyen z5362408
// 08/06/2022.

#include <stdio.h>

int main(void) {
    int students;
    int tutors;

    printf("Please enter the number of students and tutors: ");
    scanf("%d %d", &students, &tutors);

    printf("%d + %d = %d\n", students, tutors, students + tutors);

    return 0;
}