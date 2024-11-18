/*
Write a program that reads an integer A from the user and then a long integer number B with the number of digits specified by A. The program then prints out the sum of B's digits.

Guidance:
You may assume all inputs are correct (which also means you can use scanf).
You may assume the input numbers contain only digits.
You may assume all memory allocations succeed.
You may not assume bound on the size of the input number B.
Number B can't be stored using standard integer types such as int or long.

For example:

Input	Result
10      20
1111133333

*/

#include <stdio.h>
#include <stdlib.h>

void digits_sum_scanf_with_int() {
    int a;
    int b;
    scanf("%d", &a);
    int sum =0;
    for (int i=0; i < a;i++){
        scanf("%1d", b);
        sum += b;
    }
    printf("%d", sum);
}

void digits_sum_scanf_with_char() {
    int a;
    char b;
    scanf("%d", &a);
    int sum =0;
    for (int i=0; i < a;i++){
        scanf("%c", b);
        sum += b - '0';
    }
    printf("%d", sum);
}

void digits_sum_scanf_with_allocated_string() {
    int a;
    scanf("%d", a);
    char* b = (char*)malloc(a * sizeof(char));
    scanf("%s", b);
    int sum =0;
    for (int i=0; i<a;i++){
        sum += b[i] = '0';
    }
    printf("%d", sum);
    free(b);
}

void digits_sum_fgets_with_allocated_char() {
    int A;
    int sum = 0;
    char* b = (char*)malloc(100 * sizeof(char)); // Buffer to store the input line

    // Read the number of digits
    fgets(b, sizeof(b), stdin);
    sscanf(b, "%d", &A); // Convert string to integer

    fgets(b, sizeof(b), stdin);
    // Sum the digits
    for (int i = 0; i < A; i++) {
        // Read one character at a time and convert it to an integer
        if (b[i] >= '0' && b[i] <= '9') {
            sum += b[i] - '0';
        }
    }

    printf("Sum of digits: %d\n", sum);
}


int main()
{
    digits_sum_scanf_with_int();
    digits_sum_scanf_with_char();
    digits_sum_scanf_with_allocated_string();
    digits_sum_fgets_with_allocated_char();
    return 0;
}