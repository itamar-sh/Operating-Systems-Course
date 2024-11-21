#include <stdio.h>

// Function to check if a number is a power of two
int isPowerOfTwo(int n) {
    // A number must be greater than 0 and (n & (n - 1)) must be 0
    return (n > 0) && ((n & (n - 1)) == 0);
}

int main() {
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    if (isPowerOfTwo(number)) {
        printf("%d is a power of two.\n", number);
    } else {
        printf("%d is not a power of two.\n", number);
    }

    return 0;
}
