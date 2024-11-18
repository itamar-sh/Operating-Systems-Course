#include <stdio.h>
#include <string.h>

// Function to print the elements of an array
void printArrayWithKnownSize(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


// main function
int ArrayInit() {
    // 1) Declare and initalize an array with fixed size
    int numbers[5] = {10, 20, 30, 40, 50};

    // Access and print array elements with known size
    printf("Array elements:\n");
    printArrayWithKnownSize(numbers, 5);

    // modify an array element
    numbers[2] = 99;
    printf("Array after modifying the third element:\n");
    printArrayWithKnownSize(numbers, 5);

    // 2) Declare an array without init
    int uninitializedArray[5];

    for (int i = 0; i < 5; i++) {
        uninitializedArray[i] = i+1;
    }

    printf("Uninitialized array after assigning values:\n");
    printArrayWithKnownSize(uninitializedArray, 5);

    // 3) Declare and initialize a 2D array
    int multiArray[2][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("Multidimensional array elements:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", multiArray[i][j]);
        }
        printf("\n");
    }

    // 4) Declare and initialize a string array with fixed size
    const char* fruits[3] = {"Apple", "Banana", "Cherry"};
    printf("Array of strings:\n");
    for (int i = 0; i < 3; i++) {
        printf("%s ", fruits[i]);
    }
    printf("\n");
}

int main() {
    return ArrayInit();
}
