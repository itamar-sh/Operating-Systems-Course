#include <stdio.h>


void examples_using_strtok() {
    const char* input = " abc";  // String literal
    char str[100];  // A mutable buffer
    strcpy(str, input);  // Copy the string into the mutable buffer

    const char* delim = " ";  // Space is the delimiter

    // Tokenize the string
    char* token = strtok(str, delim);  // Get the first token

    // Loop through the string and print all tokens
    while (token != NULL) {
        printf("Token: '%s'\n", token);
        token = strtok(NULL, delim);  // Get the next token
    }

    // not allowed : strtok("new string without memory allocation", " ");

    return 0;
}

char* my_strtok(char* str, const char* delim) {
    static char* last = NULL;  // Static pointer to remember the last position
    if (str != NULL) {
        last = str;  // Set last to the current string on the first call
    }

    if (last == NULL) {
        return NULL;  // No more tokens
    }

    // Skip leading delimiters
    char* start = last;
    while (*start && strchr(delim, *start)) {
        start++;
    }

    // If we reach the end of the string, return NULL
    if (*start == '\0') {
        last = NULL;
        return NULL;
    }

    // Find the end of the current token
    char* end = start;
    while (*end && !strchr(delim, *end)) {
        end++;
    }

    // Terminate the token with a null character and update the 'last' pointer
    if (*end != '\0') {
        *end = '\0';
        last = end + 1;
    } else {
        last = NULL;  // No more tokens
    }

    return start;
}

int main() {
    char str[] = "Hello, how are you?";
    const char *delim = " ,?";  // Delimiters: space, comma, and question mark

    // Tokenize the string using the custom strtok implementation
    char *token = my_strtok(str, delim);
    while (token != NULL) {
        printf("Token: '%s'\n", token);
        token = my_strtok(NULL, delim);  // Get the next token
    }

    return 0;
}
