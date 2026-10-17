// week5_task4_struct_binary_io.c (BONUS)
// Name: ___Murad_____  Surname: ___Salimov_____  Student ID: __251ADB094______
//
// Task 4: Save and load a struct in binary format
// Week 5 – Files & Modular Programming
//
// Build: make lab5
// Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

int save_student_binary(const Student *s, const char *filename);
int load_student_binary(const char *filename, Student *out);
long file_size(const char *filename);

int main(void) {
    // Initialise unused name bytes before writing the record.
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";

    printf("Saving student in binary format...\n");
    if (save_student_binary(&s1, bin_file) != 0) {
        fprintf(stderr, "Failed to save binary student.\n");
        return EXIT_FAILURE;
    }

    // Save the same data as text to compare file sizes.
    FILE *fp = fopen(txt_file, "w");
    if (fp == NULL) {
        perror(txt_file);
        return EXIT_FAILURE;
    }

    int written = fprintf(fp, "%s %d %.2f\n",
                          s1.name, s1.age, s1.gpa);
    int close_result = fclose(fp);

    if (written < 0 || close_result != 0) {
        fprintf(stderr, "Failed to save text student.\n");
        return EXIT_FAILURE;
    }

    printf("Loading student from binary file...\n");
    if (load_student_binary(bin_file, &loaded) != 0) {
        fprintf(stderr, "Failed to load binary student.\n");
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n",
           loaded.name, loaded.age, loaded.gpa);

    long text_size = file_size(txt_file);
    long binary_size = file_size(bin_file);

    if (text_size < 0 || binary_size < 0) {
        fprintf(stderr, "Failed to determine file sizes.\n");
        return EXIT_FAILURE;
    }

    printf("Text file size: %ld bytes\n", text_size);
    printf("Binary file size: %ld bytes\n", binary_size);

    return EXIT_SUCCESS;
}

int save_student_binary(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1;
    }

    // Write one complete Student record.
    size_t written = fwrite(s, sizeof(Student), 1, fp);
    int close_result = fclose(fp);

    if (written != 1 || close_result != 0) {
        return -1;
    }

    return 0;
}

int load_student_binary(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    // Require one complete record; reject incomplete files.
    size_t read_count = fread(out, sizeof(Student), 1, fp);
    int close_result = fclose(fp);

    if (read_count != 1 || close_result != 0) {
        return -1;
    }

    return 0;
}

long file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    // At the end of a binary file, ftell gives its size in bytes.
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }

    long size = ftell(fp);
    int close_result = fclose(fp);

    if (size < 0 || close_result != 0) {
        return -1;
    }

    return size;
}