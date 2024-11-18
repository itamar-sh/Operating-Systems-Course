# C Tool Kit




# Common Q&A
## what happens to the line “#include <stdio.h>" during the build process?
the preprocessor replaces the line by the contents of the stdio.h file

## what is the meaning of the error "undefined reference to `func'"?
The error is produced by the linker, Alice needs to define (not declare) a function func.

