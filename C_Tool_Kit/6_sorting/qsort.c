#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Comparison functions for integers
int compare_asc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int compare_desc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

// Comparison function for strings
int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Struct definition and comparison functions
typedef struct {
    int id;
    char name[20];
    float score;
} Student;

int compare_by_id(const void *a, const void *b) {
    return ((Student *)a)->id - ((Student *)b)->id;
}

int compare_by_name(const void *a, const void *b) {
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

int compare_by_score_desc(const void *a, const void *b) {
    float diff = ((Student *)b)->score - ((Student *)a)->score;
    return (diff > 0) - (diff < 0); // Returns 1, -1, or 0
}

int main() {
    // Example 1: Sorting integers (ascending and descending)
    int arr[] = {5, 3, 8, 1, 2};
    size_t n_int = sizeof(arr) / sizeof(arr[0]);

    printf("Original integers: ");
    for (size_t i = 0; i < n_int; i++) printf("%d ", arr[i]);
    printf("\n");

    // Sort ascending
    qsort(arr, n_int, sizeof(int), compare_asc);
    printf("Sorted ascending: ");
    for (size_t i = 0; i < n_int; i++) printf("%d ", arr[i]);
    printf("\n");

    // Sort descending
    qsort(arr, n_int, sizeof(int), compare_desc);
    printf("Sorted descending: ");
    for (size_t i = 0; i < n_int; i++) printf("%d ", arr[i]);
    printf("\n\n");

    // Example 2: Sorting strings
    const char *str_arr[] = {"apple", "orange", "banana", "kiwi"};
    size_t n_str = sizeof(str_arr) / sizeof(str_arr[0]);

    printf("Original strings:\n");
    for (size_t i = 0; i < n_str; i++) printf("%s\n", str_arr[i]);

    qsort(str_arr, n_str, sizeof(const char *), compare_strings);
    printf("Sorted strings:\n");
    for (size_t i = 0; i < n_str; i++) printf("%s\n", str_arr[i]);
    printf("\n");

    // Example 3: Sorting structs
    Student students[] = {
        {101, "Alice", 88.5},
        {103, "Bob", 72.0},
        {102, "Charlie", 91.0},
    };
    size_t n_struct = sizeof(students) / sizeof(students[0]);

    printf("Original students:\n");
    for (size_t i = 0; i < n_struct; i++) {
        printf("ID: %d, Name: %s, Score: %.2f\n", students[i].id, students[i].name, students[i].score);
    }

    // Sort by ID
    qsort(students, n_struct, sizeof(Student), compare_by_id);
    printf("\nSorted by ID:\n");
    for (size_t i = 0; i < n_struct; i++) {
        printf("ID: %d, Name: %s, Score: %.2f\n", students[i].id, students[i].name, students[i].score);
    }

    // Sort by Name
    qsort(students, n_struct, sizeof(Student), compare_by_name);
    printf("\nSorted by Name:\n");
    for (size_t i = 0; i < n_struct; i++) {
        printf("ID: %d, Name: %s, Score: %.2f\n", students[i].id, students[i].name, students[i].score);
    }

    // Sort by Score (Descending)
    qsort(students, n_struct, sizeof(Student), compare_by_score_desc);
    printf("\nSorted by Score (Descending):\n");
    for (size_t i = 0; i < n_struct; i++) {
        printf("ID: %d, Name: %s, Score: %.2f\n", students[i].id, students[i].name, students[i].score);
    }

    return 0;
}
