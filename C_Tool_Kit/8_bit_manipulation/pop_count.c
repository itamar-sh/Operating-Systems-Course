/*
Write a function called size_t my_pop_count(unsigned int) that preforms binary population count on an int: the function counts how many of the bits are on ("1").
*/
#include <stddef.h>
#include <stdio.h>


size_t pop_count(unsigned int num) {
    size_t result = 0;
    size_t indicator = 1;
    while (indicator > 0) {
        if (num & indicator) {
            result += 1;
        }
        indicator = indicator << 1;
    }
    return result;
}


int main() {
    fprintf(stdout, "%zu \n", pop_count(16));  // 10000 -> 1
    fprintf(stdout, "%zu \n", pop_count(15));  // 1111 -> 4
    fprintf(stdout, "%zu \n", pop_count(4147483647));
    fprintf(stdout, "%zu \n", pop_count(-3));
    fprintf(stdout, "%zu \n", pop_count(4294967293));
}