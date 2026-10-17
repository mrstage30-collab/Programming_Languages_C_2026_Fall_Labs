/*
 * week4_1_dynamic_array.c
 * Author: [Murad Salimov]
 * Student ID: [251ADB094]
 * Description:
 *   Allocates an integer array, reads values, prints their sum
 *   and average, and frees the allocated memory.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int *arr = NULL;
    long long sum = 0;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    /* Prevent the allocation size from overflowing. */
    if ((size_t)n > SIZE_MAX / sizeof(int)) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            printf("Invalid input.\n");
            return 1;
        }
        sum += arr[i];
    }

    /* Convert to double before division to retain decimals. */
    double average = (double)sum / n;

    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", average);

    free(arr);
    return 0;
}