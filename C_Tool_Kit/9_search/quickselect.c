#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // For srand() and rand()

// Partition function for quickselect
int partition(int* arr, int low, int high) {
    // Swap arr[pivotIndex] with arr[high] to make arr[high] the pivot
    int pivotIndex = low + rand() % (high - low + 1);
    int temp = arr[pivotIndex];
    arr[pivotIndex] = arr[high];
    arr[high] = temp;

    int pivot = arr[high];

    int i = low - 1; // start at -1 in the first time

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {  // from j (include) the elements bigger than pivot
            i++;  // from i (include) to j (exclude) the elements smaller (and equal) than pivot
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];  // swap pivot to be on first j section element.
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Quickselect function to find the k-th smallest element
int quickselect(int* arr, int low, int high, int k) {
    if (low <= high) {
        int pivot = partition(arr, low, high);

        if (pivot == k)
            return arr[pivot];
        else if (pivot < k)
            return quickselect(arr, pivot + 1, high, k);
        else
            return quickselect(arr, low, pivot - 1, k);
    }
    return -1;
}

int main() {
    int* arr = (int*)malloc(5 * sizeof(int));  // Dynamically allocate memory
    arr[0] = 50;
    arr[1] = 30;
    arr[2] = 40;
    arr[3] = 10;
    arr[4] = 20;

    int k = 3;  // Find the 3rd smallest element
    int size = 5;

    // Find k-th smallest element (k-1 because the index is 0-based)
    int result = quickselect(arr, 0, size - 1, k - 1);
    printf("The %d-th smallest element is %d\n", k, result);

    // Free the dynamically allocated memory
    free(arr);

    return 0;
}
