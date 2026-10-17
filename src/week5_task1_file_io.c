// week5_task1_file_io.c
// Name: ___Murad_____  Surname: ___Salimov_____  Student ID: __251ADB094______
//
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task1_file_io

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    const char *filename = DEFAULT_FILENAME;
    char line[LINE_LEN];
    int line_count = 0;

    // Use the command-line filename when provided.
    if (argc > 1) {
        filename = argv[1];
    }

    printf("Writing lines to %s...\n", filename);

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    // Track write errors while ensuring the file is closed.
    int write_failed = 0;

    if (fprintf(fp, "Hello, file I/O in C!\n"
                    "This is another line.\n") < 0) {
        write_failed = 1;
    }

    if (fclose(fp) != 0) {
        write_failed = 1;
    }

    if (write_failed) {
        fprintf(stderr, "Failed to write file.\n");
        return EXIT_FAILURE;
    }

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    printf("Reading contents:\n");

    // Read and print each line, counting successful reads.
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
        line_count++;
    }

    int read_failed = ferror(fp);

    if (fclose(fp) != 0) {
        read_failed = 1;
    }

    if (read_failed) {
        fprintf(stderr, "Failed to read file.\n");
        return EXIT_FAILURE;
    }

    printf("Lines read: %d\n", line_count);

    return EXIT_SUCCESS;
}