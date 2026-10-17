// week5_task2_struct_save_load.c
// Name: ___Murad_____  Surname: ___Salimov_____  Student ID: __251ADB094______
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

int save_student(const Student *s, const char *filename);
int load_student(const char *filename, Student *out);

int main(void) {
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *filename = "student.txt";

    printf("Saving student to file...\n");
    if (save_student(&s1, filename) != 0) {
        fprintf(stderr, "Failed to save student.\n");
        return EXIT_FAILURE;
    }

    printf("Loading student from file...\n");
    if (load_student(filename, &loaded) != 0) {
        fprintf(stderr, "Failed to load student.\n");
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n",
           loaded.name, loaded.age, loaded.gpa);

    return EXIT_SUCCESS;
}

int save_student(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }

    // Store all fields on one line, separated by spaces.
    int result = fprintf(fp, "%s %d %.2f\n",
                         s->name, s->age, s->gpa);

    // Closing can also fail when buffered data is written.
    int close_result = fclose(fp);

    if (result < 0 || close_result != 0) {
        return -1;
    }

    return 0;
}

int load_student(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    // Limit the name length and require all three fields.
    int result = fscanf(fp, "%49s %d %f",
                        out->name, &out->age, &out->gpa);

    int close_result = fclose(fp);

    if (result != 3 || close_result != 0) {
        return -1;
    }

    return 0;
}