# SSBC assembler and compiler

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
