#include <stdio.h>
#include <ctype.h>

void check_character(char c) {
    printf("Character: '%c' (ASCII: %d)\n", c, c);

    // Character Classification
    if (isalnum(c)) {
        printf(" - isalnum: Character is alphanumeric (letter or digit).\n");
    }

    if (isalpha(c)) {
        printf(" - isalpha: Character is alphabetic (a letter).\n");
    }

    if (isdigit(c)) {
        printf(" - isdigit: Character is a digit (0-9).\n");
    }

    if (islower(c)) {
        printf(" - islower: Character is lowercase.\n");
    }

    if (isupper(c)) {
        printf(" - isupper: Character is uppercase.\n");
    }

    if (isxdigit(c)) {
        printf(" - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).\n");
    }

    if (ispunct(c)) {
        printf(" - ispunct: Character is punctuation.\n");
    }

    if (isgraph(c)) {
        printf(" - isgraph: Character has a graphical representation (not a space).\n");
    }

    if (iscntrl(c)) {
        printf(" - iscntrl: Character is a control character.\n");
    }

    if (isblank(c)) {
        printf(" - isblank: Character is a blank space or tab.\n");
    }

    // Character Conversion
    if (isupper(c)) {
        printf(" - tolower: '%c' converted to lowercase is '%c'.\n", c, tolower(c));
    }

    if (islower(c)) {
        printf(" - toupper: '%c' converted to uppercase is '%c'.\n", c, toupper(c));
    }

    printf("\n");
}

int main() {
    // Loop over the entire ASCII table (from 0 to 127)
    for (int i = 0; i < 128; i++) {
        check_character((char)i);
    }

    return 0;
}


/*
Character: '' (ASCII: 0)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 1)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 2)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 3)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 4)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 5)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 6)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 7)
 - iscntrl: Character is a control character.

Character: ' (ASCII: 8)
 - iscntrl: Character is a control character.

Character: '	' (ASCII: 9)
 - iscntrl: Character is a control character.
 - isblank: Character is a blank space or tab.

Character: '
' (ASCII: 10)
 - iscntrl: Character is a control character.

Character: '
            ' (ASCII: 11)
 - iscntrl: Character is a control character.

Character: '
            ' (ASCII: 12)
 - iscntrl: Character is a control character.

' (ASCII: 13)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 14)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 15)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 16)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 17)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 18)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 19)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 20)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 21)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 22)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 23)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 24)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 25)
 - iscntrl: Character is a control character.

Character: '�' (ASCII: 26)
 - iscntrl: Character is a control character.

Character: 'SCII: 27)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 28)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 29)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 30)
 - iscntrl: Character is a control character.

Character: '' (ASCII: 31)
 - iscntrl: Character is a control character.

Character: ' ' (ASCII: 32)
 - isblank: Character is a blank space or tab.

Character: '!' (ASCII: 33)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '"' (ASCII: 34)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '#' (ASCII: 35)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '$' (ASCII: 36)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '%' (ASCII: 37)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '&' (ASCII: 38)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: ''' (ASCII: 39)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '(' (ASCII: 40)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: ')' (ASCII: 41)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '*' (ASCII: 42)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '+' (ASCII: 43)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: ',' (ASCII: 44)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '-' (ASCII: 45)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '.' (ASCII: 46)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '/' (ASCII: 47)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '0' (ASCII: 48)
 - isalnum: Character is alphanumeric (letter or digit).
 - isdigit: Character is a digit (0-9).
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).

Character: '1' (ASCII: 49)
 - isalnum: Character is alphanumeric (letter or digit).
 - isdigit: Character is a digit (0-9).
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).

Character: '2' (ASCII: 50)
 - isalnum: Character is alphanumeric (letter or digit).
 - isdigit: Character is a digit (0-9).
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).

Character: '3' (ASCII: 51)
 - isalnum: Character is alphanumeric (letter or digit).
 - isdigit: Character is a digit (0-9).
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).

Character: '4' (ASCII: 52)
 - isalnum: Character is alphanumeric (letter or digit).
 - isdigit: Character is a digit (0-9).
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).

Character: '5' (ASCII: 53)
 - isalnum: Character is alphanumeric (letter or digit).
 - isdigit: Character is a digit (0-9).
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).

Character: '6' (ASCII: 54)
 - isalnum: Character is alphanumeric (letter or digit).
 - isdigit: Character is a digit (0-9).
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).

Character: '7' (ASCII: 55)
 - isalnum: Character is alphanumeric (letter or digit).
 - isdigit: Character is a digit (0-9).
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).

Character: '8' (ASCII: 56)
 - isalnum: Character is alphanumeric (letter or digit).
 - isdigit: Character is a digit (0-9).
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).

Character: '9' (ASCII: 57)
 - isalnum: Character is alphanumeric (letter or digit).
 - isdigit: Character is a digit (0-9).
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).

Character: ':' (ASCII: 58)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: ';' (ASCII: 59)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '<' (ASCII: 60)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '=' (ASCII: 61)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '>' (ASCII: 62)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '?' (ASCII: 63)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '@' (ASCII: 64)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: 'A' (ASCII: 65)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'A' converted to lowercase is 'a'.

Character: 'B' (ASCII: 66)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'B' converted to lowercase is 'b'.

Character: 'C' (ASCII: 67)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'C' converted to lowercase is 'c'.

Character: 'D' (ASCII: 68)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'D' converted to lowercase is 'd'.

Character: 'E' (ASCII: 69)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'E' converted to lowercase is 'e'.

Character: 'F' (ASCII: 70)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'F' converted to lowercase is 'f'.

Character: 'G' (ASCII: 71)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'G' converted to lowercase is 'g'.

Character: 'H' (ASCII: 72)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'H' converted to lowercase is 'h'.

Character: 'I' (ASCII: 73)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'I' converted to lowercase is 'i'.

Character: 'J' (ASCII: 74)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'J' converted to lowercase is 'j'.

Character: 'K' (ASCII: 75)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'K' converted to lowercase is 'k'.

Character: 'L' (ASCII: 76)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'L' converted to lowercase is 'l'.

Character: 'M' (ASCII: 77)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'M' converted to lowercase is 'm'.

Character: 'N' (ASCII: 78)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'N' converted to lowercase is 'n'.

Character: 'O' (ASCII: 79)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'O' converted to lowercase is 'o'.

Character: 'P' (ASCII: 80)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'P' converted to lowercase is 'p'.

Character: 'Q' (ASCII: 81)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'Q' converted to lowercase is 'q'.

Character: 'R' (ASCII: 82)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'R' converted to lowercase is 'r'.

Character: 'S' (ASCII: 83)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'S' converted to lowercase is 's'.

Character: 'T' (ASCII: 84)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'T' converted to lowercase is 't'.

Character: 'U' (ASCII: 85)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'U' converted to lowercase is 'u'.

Character: 'V' (ASCII: 86)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'V' converted to lowercase is 'v'.

Character: 'W' (ASCII: 87)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'W' converted to lowercase is 'w'.

Character: 'X' (ASCII: 88)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'X' converted to lowercase is 'x'.

Character: 'Y' (ASCII: 89)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'Y' converted to lowercase is 'y'.

Character: 'Z' (ASCII: 90)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - isupper: Character is uppercase.
 - isgraph: Character has a graphical representation (not a space).
 - tolower: 'Z' converted to lowercase is 'z'.

Character: '[' (ASCII: 91)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '\' (ASCII: 92)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: ']' (ASCII: 93)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '^' (ASCII: 94)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '_' (ASCII: 95)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '`' (ASCII: 96)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: 'a' (ASCII: 97)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'a' converted to uppercase is 'A'.

Character: 'b' (ASCII: 98)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'b' converted to uppercase is 'B'.

Character: 'c' (ASCII: 99)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'c' converted to uppercase is 'C'.

Character: 'd' (ASCII: 100)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'd' converted to uppercase is 'D'.

Character: 'e' (ASCII: 101)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'e' converted to uppercase is 'E'.

Character: 'f' (ASCII: 102)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isxdigit: Character is a hexadecimal digit (0-9, a-f, A-F).
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'f' converted to uppercase is 'F'.

Character: 'g' (ASCII: 103)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'g' converted to uppercase is 'G'.

Character: 'h' (ASCII: 104)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'h' converted to uppercase is 'H'.

Character: 'i' (ASCII: 105)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'i' converted to uppercase is 'I'.

Character: 'j' (ASCII: 106)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'j' converted to uppercase is 'J'.

Character: 'k' (ASCII: 107)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'k' converted to uppercase is 'K'.

Character: 'l' (ASCII: 108)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'l' converted to uppercase is 'L'.

Character: 'm' (ASCII: 109)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'm' converted to uppercase is 'M'.

Character: 'n' (ASCII: 110)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'n' converted to uppercase is 'N'.

Character: 'o' (ASCII: 111)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'o' converted to uppercase is 'O'.

Character: 'p' (ASCII: 112)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'p' converted to uppercase is 'P'.

Character: 'q' (ASCII: 113)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'q' converted to uppercase is 'Q'.

Character: 'r' (ASCII: 114)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'r' converted to uppercase is 'R'.

Character: 's' (ASCII: 115)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 's' converted to uppercase is 'S'.

Character: 't' (ASCII: 116)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 't' converted to uppercase is 'T'.

Character: 'u' (ASCII: 117)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'u' converted to uppercase is 'U'.

Character: 'v' (ASCII: 118)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'v' converted to uppercase is 'V'.

Character: 'w' (ASCII: 119)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'w' converted to uppercase is 'W'.

Character: 'x' (ASCII: 120)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'x' converted to uppercase is 'X'.

Character: 'y' (ASCII: 121)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'y' converted to uppercase is 'Y'.

Character: 'z' (ASCII: 122)
 - isalnum: Character is alphanumeric (letter or digit).
 - isalpha: Character is alphabetic (a letter).
 - islower: Character is lowercase.
 - isgraph: Character has a graphical representation (not a space).
 - toupper: 'z' converted to uppercase is 'Z'.

Character: '{' (ASCII: 123)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '|' (ASCII: 124)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '}' (ASCII: 125)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '~' (ASCII: 126)
 - ispunct: Character is punctuation.
 - isgraph: Character has a graphical representation (not a space).

Character: '' (ASCII: 127)
 - iscntrl: Character is a control character.

*/
