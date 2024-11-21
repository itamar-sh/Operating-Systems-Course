#include <stdio.h>

#pragma pack(push, 1)  // Disable padding

struct PackedStruct {
    char a;
    int b;
    char c;
};

struct Inner {
    int x;
    int y;
};

struct Outer {
    char a;
    struct Inner innerStruct;
    double b;
};


struct arr_struct {
    int a[10];
};

struct arr_struct_poiter {
    int* a;
};

struct EmptyStruct {
};

struct LongStruct {
    long double a;
};

struct LongIntStruct {
    long int a;
};

#pragma pack(pop)

int main() {
    struct PackedStruct example;
    printf("Size of PackedStruct: %zu bytes\n", sizeof(example));

    struct Inner inner;
    printf("Size of Inner: %zu bytes\n", sizeof(inner));

    struct Outer outer;
    printf("Size of Outer: %zu bytes\n", sizeof(outer));

    struct arr_struct arr_struct;
    printf("Size of arr_struct: %zu bytes\n", sizeof(arr_struct));

    struct arr_struct_poiter arr_struct_pointer;
    printf("Size of arr_struct_pointer: %zu bytes\n", sizeof(arr_struct_pointer));

    struct EmptyStruct empty;
    printf("Size of EmptyStruct: %zu bytes\n", sizeof(empty));

    struct LongStruct long_struct;
    printf("Size of LongStruct: %zu bytes\n", sizeof(long_struct));

    struct LongIntStruct long_int_struct;
    printf("Size of LongIntStruct: %zu bytes\n", sizeof(long_int_struct));

    return 0;
}
