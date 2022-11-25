
// Written by Jayden Nguyen z5362408
// on 2206/2022
//
// Interactive program to scan in and display the details of students in a
// class.

#include <stdio.h>

#define MAX_CLASS_SIZE 20
#define MAX_EXAM_MARK 40
#define MAX_ASSIGMENTS_MARK 60

// UNSW COMPSCI major codes
enum major {
    COMPA1,
    COMPD1,
    COMPE1,
    COMPI1,
    COMPJ1,
    COMPN1,
    COMPS1,
    COMPY1,
    NONE
};

// Struct representing a UNSW COMPSCI student
struct student {
    int z_id;
    enum major major;
    double assignments_mark;
    double exam_mark;
    double course_grade;
};

int init_class_size() {
    int class_size;
    printf("Enter Class Size: ");
    scanf("%d", &class_size);

    if (class_size <= 0 || class_size > MAX_CLASS_SIZE) {
        printf("Class Size must be between 1 and %d\n", MAX_CLASS_SIZE);
        // Exit the program early
        return 0;
    }

    return class_size;
}

void print_major(enum major major) {
    if (major == COMPA1) {
        printf("Computer Science\n");
    } else if (major == COMPD1) {
        printf("Database Systems\n");
    } else if (major == COMPE1) {
        printf("eCommerce Systems\n");
    } else if (major == COMPI1) {
        printf("Artificial Intelligence\n");
    } else if (major == COMPJ1) {
        printf("Programming Languages\n");
    } else if (major == COMPN1) {
        printf("Computer Networks\n");
    } else if (major == COMPS1) {
        printf("Embedded Systems\n");
    } else if (major == COMPY1) {
        printf("Security Engineering\n");
    } else {
        printf("None\n");
    }

}

enum major assign_majors(void) {
    printf("Select Major: \n");
    enum major major = COMPA1;
    while (major <= NONE) {
        printf("%d: ", major);
        print_major(major);
        major++;
    }
    return major;
}

void enrol_students(int class_size, struct student class[MAX_CLASS_SIZE]) {
    int i = 0;
    while (i < class_size) {
        printf("Student %d: \n", i + 1);
        struct student new_student;
        printf("Enter zID: ");
        scanf("%d", &new_student.z_id);

        enum major major = assign_majors();

        printf(": ");
        int scanned_major;
        scanf("%d", &scanned_major);
        major = NONE;
        if (scanned_major >= COMPA1 && scanned_major < NONE) {
            major = scanned_major;
        }

        new_student.major = major;

        printf("Enter Assignments mark (out of %d): ", MAX_ASSIGMENTS_MARK);
        scanf("%lf", &new_student.assignments_mark);

        printf("Enter exam mark (out of %d): ", MAX_EXAM_MARK);
        scanf("%lf", &new_student.exam_mark);

        new_student.course_grade = new_student.exam_mark 
                                 + new_student.assignments_mark;

        class[i] = new_student;
        i++;
    }
}
 
void print_student_marks(struct student student) {
    printf("\tAssignments Mark: %3.02lf/%d\n", student.assignments_mark, 
            MAX_ASSIGMENTS_MARK);
    printf("\tExam Mark: %3.02lf/%d\n", student.exam_mark, MAX_EXAM_MARK);
    printf("\tCourse Grade: %3.02lf/%d\n", student.course_grade, 
            MAX_ASSIGMENTS_MARK + MAX_EXAM_MARK);
    printf("}\n");
}


int main(void) {
    int class_size = init_class_size();

    struct student class[MAX_CLASS_SIZE];

    enrol_students(class_size, class);

    printf("Students: \n");
    int i = 0;
    while (i < class_size) {
        struct student student = class[i];
        printf("z%07d: {\n", student.z_id);

        printf("\tMajor: ");
        print_major(student.major);
        print_student_marks(student);

        i++;
    }

    return 0;
}
