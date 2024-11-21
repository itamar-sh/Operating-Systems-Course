#include <math.h>  // Include math.h to use pow()


unsigned int djb2Hash(int key) {
    /*
    DJB2 Hash Function
    This is a simple yet effective hash function created by Daniel J. Bernstein.
    It uses bitwise operations and prime numbers to generate a hash value.
    */
    unsigned int prime = 5381;
    unsigned int base_exponent = 5;  // 2^5 givees us: 2*32, we will add the prime one more to get 33.
    // prime - 5381, exponent - 33.
    return ((prime << base_exponent) + prime) + key; // prime ^ exponent (33 here) + key
}

unsigned int djb2Hash2(int key) {
    /*
    DJB2 Hash Function
    This is a simple yet effective hash function created by Daniel J. Bernstein.
    It uses bitwise operations and prime numbers to generate a hash value.
    */
    unsigned int prime = 5381;
    unsigned int exponent = 33;
    return pow(prime, exponent) + key; // (prime ** exponent) + key
}