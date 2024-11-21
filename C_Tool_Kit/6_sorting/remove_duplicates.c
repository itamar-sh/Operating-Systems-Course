#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort (ascending order)
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Function to remove duplicates from a sorted array
int removeDuplicates(int* arr, int size) {
    if (size == 0) return 0;  // Edge case: empty array

    int newSize = 1;  // Start with the first element as unique

    // Iterate over the sorted array to remove duplicates
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[newSize - 1]) {
            arr[newSize] = arr[i];
            newSize++;
        }
    }

    return newSize;  // Return the new size of the array
}

int main() {
    int arr[] = {5, 3, 8, 5, 2, 8, 3, 9, 1, 3, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Sort the array using qsort
    qsort(arr, size, sizeof(int), compare);

    // Remove duplicates
    int newSize = removeDuplicates(arr, size);

    // Print the sorted array after removing duplicates
    printf("Sorted array after removing duplicates:\n");
    for (int i = 0; i < newSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
