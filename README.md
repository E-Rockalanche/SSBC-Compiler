# SSBC assembler and compiler

c-like language to SSBC assembly compiler. Made for CSCI 405 (meta programming) class project. Based on older compiler made for use in CSCI 261 (assembly programming) (courses offered at Vancouver Island University)

The SSBC (Simple stack based computer) is a teaching tool used by [Peter Walsh](http://csciun1.mala.bc.ca:8080/~pwalsh/) in CSCI 261 to teach students the basics of assembly programming. The SSBC has a 16bit address space, 11 instructions, 4 IO ports, stack, and program status available to the programmer. The stack pointer and program counter are not accessible. The program status contains a negative and a zero flag. No carry or overflow flags are implemented.

SSBC instruction set:
```
0: NOOP
1: HALT
2: PUSHIMM
3: PUSHEXT
4: POPINH
5: POPEXT
6: JNZ
7: JNN
8: ADD
9: SUB
10: NOR
```

The purpose of this project is to see if a high level language could be compiled into these 11 (10 excluding noop) opcodes. Future work includes proper function scoping, sructs, object orientation.

## Directory Structure

### assembler
	-contains source code for ssbc assembler
	-build with makefile
	-ssbc language documentation in "ssbc assembly language manual.txt"
	***building assembler is not required to use compiler***

### compiler:
	-contains source code for high level language compiler (language not yet named)
	-build with makefile
	-grammar for language in "HLL manual.txt"

### lang:
	-contains abstract class for language tokens

### obj:
	-contains object files for programs

### ssbc:
	-contains source code for ssbc emulator
	-build with makefile

### ssbclib:
	-contains ssbc assembly files needed by the compiler to perform 16 bit math

### tokenizer:
	-contains source code for generic tokenizer used by assembler and compiler
	(thinking of replacing this with state machines for each program.
	right now the tokenizer/lang combo have problems with strings, comments,
	and hex numbers)

### tool:
	-contains useful stuff

## Programs

***makefiles create programs in root directory***

### assembler
	-assembles ssbc assembly files to binary
execute with command:
./ssbca <files to assemble> -o <output file> [-w (set warnings)] [-c (output comments in output file)]

### compiler
	-compiles high level language to binary
	-also generates assembly file <output file>.ssbc (compiled HLL before assembly)
execute with command:
./compiler <files to compiler> -o <output file>

### ssbc
	-simple stack based computer emulator
	-loads and runs ssbc binary files
execute with command:
./ssbc

## Contributors
[Eric Roberts](https://github.com/E-Rockalanche)
