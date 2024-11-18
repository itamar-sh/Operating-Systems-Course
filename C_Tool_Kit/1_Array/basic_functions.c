#include <stdio.h>
#include <stdlib.h>

// Function to append an element to a dynamic array
int* append(int* array, int* size, int* capacity, int value) {
    // Check if we need to expand the array
    if (*size >= *capacity) {
        *capacity *= 2;  // Double the capacity
        array = realloc(array, *capacity * sizeof(int));
        if (array == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);  // Exit if reallocation fails
        }
    }
    array[*size] = value;
    (*size)++;
    return array;
}

// Function to find the minimum element in an array
int min_array(int* arr, int n) {
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// Function to find the maximum element in an array
int max_array(int* arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int size = 0;
    int capacity = 2;  // Initial capacity
    int* array = malloc(capacity * sizeof(int));

    // Append elements to the dynamic array
    array = append(array, &size, &capacity, 10);
    array = append(array, &size, &capacity, 20);
    array = append(array, &size, &capacity, 5);
    array = append(array, &size, &capacity, 25);

    // Find min and max values
    printf("Minimum element: %d\n", min_array(array, size));
    printf("Maximum element: %d\n", max_array(array, size));

    // Free memory when done
    free(array);

    return 0;
}
