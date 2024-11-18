# String
There is no string object in C, we use char* instead.

But there is a library called <string.h> that give us some methods we can activate on char*.

## String.h

### Info

### strlen(const char* str)
Return the length of the string str. Excluding the null terminator ('\0').

### Copy

### strcpy(char* dest, const char* src)
Copies the string src to dest. Including the null terminator('\0').

### strncpy(char* dest, const char* src, size_t n)
Copies up to n characters from the src to dest.

### strcat(char* dest, const char* src)
Appends the string src to the end of dest.

### strncat(char* dest, const char* src, size_t n)
Appends up to n characters from src to the end of dest.

### Comparison

### strcmp(const char* str1, const char* str2)
Compares the strings str1 and str2 return 0 if they are equal, a negative value if str is less then str2, and a positive value if str1 is greater.

### strncmp(const char* str1, const char* str2, size_t n)
Compares up to n characters of str1 and str2.

### Search

### strchr(const char* str, int c)
Finds the first occurrence of the character c in string str.

### strrchr(const char* str, int c)
Finds the last occurrence of the character c in the string str.

### strstr(const char* haystack, const char* needle)
Finds the first occurrence of the substring needle in the string haystack.

### Split ?

### strtok(char* str, const char* delim)
Tokenizes a string str using the delimiter(s) delim.

### Memoery manipulation

### memcpy(void* dest, const void* src, size_t n)
Copies n bytes from memory area src to memory area dest.

### memove(void* dest, const void* src, size_t n)
Copies n bytes from src to dest allowing the source and destination to overlap.

### memset(void* str, int c, size_t n)
Fills the first n bytes of the memory area str with the byte c.

### memcmp(const void* str1, const void* str2, size_t n)
Compares the first n bytes of the memory areas str1 and str2.

### Create

### strdup(const char* str)
Create a dupplicate of the string str.

### strerro(int errnum)
Return a pointer to a string describing the error code errnum.
