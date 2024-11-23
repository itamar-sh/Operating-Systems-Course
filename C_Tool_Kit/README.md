# C Tool Kit




# Common Q&A
## what happens to the line “#include <stdio.h>" during the build process?
the preprocessor replaces the line by the contents of the stdio.h file

## what is the meaning of the error "undefined reference to `func'"?
The error is produced by the linker, Alice needs to define (not declare) a function func.

## What are the advantages of a static library over a dynamic library?
- Independent of the versions of the libraries.
- Independent of the presence/location of the libraries at run time.

Keep in mind that you still:
You do need to re-compile the code every time you want the latest version of the library.
Multiple processes does not share the same code (They copying it).
It's not make your executables smaller.

## Which of the following statements is correct about char* and void*?
- char* allows us to manipulate a single byte.
- No pointer arithmetic is defined for void*
- Dereferencing is not allowed for void*
- sizeof(char *) == sizeof(void *)

## What’s the meaning of following declaration in C language: float* foo(int);
foo is a functtion that gets int and return a pointer to float.

## What’s the meaning of following declaration in C language: void (*foo(void))(void);
foo is a function that gets nothing and return a function that get nothing and return nothing.

## What’s the meaning of following declaration in C language: float *(*foo(void))(int);
foo is a function that gets nothing and returns a pointer to a function which gets an int and returns a pointer to float

## In what cases is a NULL terminator ('\0') automatically added to a string?
- When initializing a char* from a string literal.
- When initializing an array from a string literal.

## explain what is 'a' in: int a[10];
`a` represents the entire array.
However, in most expressions, `a` decays to a pointer to its first element, effectively becoming `&a[0]`.
This means a can be used as a pointer to access array elements.
`sizeof(a)` gives the size of the entire array (int[10]), typically `10 * sizeof(int)` bytes.
`sizeof(*a)` gives the size of a single int (the type of the first element in the array).
`sizeof(&a)` gives the size of a pointer to the array `(int(*)[10])`, which is the size of a pointer.
Printing `a` will require cast him to a pointer: ` printf("Address of the first element: %p\n", (void*)a); `

## What is a char literal and what is a string literal in C?
In C, char literals and string literals are both used to represent characters or sequences of characters, but they differ in their types and how they are stored in memory:

`char c = 'a';`
char literal 'a' - actually represented by its ASCII value, which is 97 for the character 'a'.
It is of type int in C, not char. sizeof 4.

`char *str = "Hello";`
A string literal is a sequence of characters followed by a null terminator ('\0').
The string "Hello" is represented as an array of characters: {'H', 'e', 'l', 'l', 'o', '\0'}.
It is of type char[] (array of char) or can be assigned to a pointer of type char*.
sizeof the string + 1 (for null terminator).

## What is the difference between `int (*a)[5];` and `int *b[5];`
`a` is a pointer to an array of 5 integers.
`b` is a represents of an array of 5 int*, 5 pointers to int.

## Choose the correct description for the following statement: `char (* ( *f())[])();`
declaration of the function f which receives no parameters and returns a pointer to an array of pointers to functions that receive no parameters and return a char

## What is Linkeage in C?
Linkage in C/C++ refers to the process by which the linker connects different parts of a program, such as functions and variables, across multiple translation units (i.e., source files). It is the mechanism that enables the program's components to reference and use each other, resolving references between object files and libraries.

-Types of Linkage: External Linkage, Internal Linkage, No Linkage.
-A function or variable with external linkage can be accessed from other translation units.
-Global variables and functions defined outside any function have external linkage by default.
-A function or variable with internal linkage can only be accessed within the translation unit where it is defined.
-static functions and variables have internal linkage.
-Local variables inside a function have no linkage.
-If you define the same function or variable in multiple translation units without proper mechanisms like inline or extern, the linker will find multiple definitions, leading to a linkage error (often called a "multiple definition" error).
If a function is declared as extern in one translation unit and defined in another, the linker will resolve the reference correctly.
inline keyword on a function definition, tells the compiler to treat it as a candidate for inlining and avoids multiple definitions at link time.




