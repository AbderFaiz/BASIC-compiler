# BASIC-compiler
BASIC compiler into C

## Overview

This project is a compiler that translates BASIC source code into C.

> **Note:**  
> This repository includes an implementation in C++ of the ["Teeny Tiny Compiler" tutorial by Austin Henley](https://austinhenley.com/blog/teenytinycompiler1.html).  
> The code follows the steps and concepts from the tutorial, providing a minimal compiler example for educational purposes.


## Features

- Parses a subset of the BASIC language
- Generates readable and compilable C code
- Command-line interface for compiling BASIC files

## Usage

1. Clone the repository:
  ```sh
  git clone https://github.com/yourusername/BASIC-compiler.git
  cd BASIC-compiler
  ```

2. Build the compiler (example using `make`):
  ```sh
  make
  ```

3. Compile a BASIC file:
  ```sh
  ./basic-compiler source.bas
  ```

4. Compile the generated C code:
  ```sh
  gcc out.c -o program
  ```

5. Run your program:
  ```sh
  ./program
  ```

## Example

Given a BASIC file `examples/factorial`:
```basic
LABEL START
PRINT "Enter a number to compute its factorial:"
INPUT n
PRINT ""

LET result = 1

WHILE n > 1 REPEAT
    LET result = result * n
    LET n = n - 1
ENDWHILE
PRINT "The factorial is:"
PRINT result
PRINT ""
GOTO START

```

Compile and run:
```sh
./basic-compiler examples/factorial
gcc out.c -o factorial
./factorial
```
Produced c code is:
```c
#include <stdio.h>
int main(void){
float n;
float result;
START: printf("Enter a number to compute its factorial:\n");
if (0 == scanf("%f", &n)){
n = 0;
scanf("%*s");
}
printf("\n");
result = 1;
while(n>1){
result = result*n;
n = n-1;
}
printf("The factorial is:\n");
printf("%.2f\n", (float)(result));
printf("\n");
goto START;
return 0;
}
```

## TODO

- [ ]   Parentheses for expressions
- [ ]   Logical operators (and, or, not)
- [ ]   ELSE IF and ELSE
- [ ]   FOR loop
- [ ]   Number literals written in binary, hex, and octal
- [ ]   Better compiler errors (e.g., what line the error occurred)
- [ ]   Allow multiple code files
- [ ]   Functions with parameters and return values
- [ ]   Lexical scope (see [scope](https://en.wikipedia.org/wiki/Scope_(computer_science)))
- [ ]   Standard library (e.g., file operations)
- [ ]   [Abstract syntax tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree) representation
- [ ]   More primitive types (e.g., integer, strings, boolean)
- [ ]   Arrays
- [ ]   Record types (i.e., structs or tuples)
- [ ]   Type checking (see [type systems](https://en.wikipedia.org/wiki/Type_system))
- [ ]   Compiler optimizations (e.g., [constant folding](https://en.wikipedia.org/wiki/Constant_folding))
- [ ]   Test cases for the compiler (see [unit testing](https://en.wikipedia.org/wiki/Unit_testing) and [test-driven development](https://en.wikipedia.org/wiki/Test-driven_development))