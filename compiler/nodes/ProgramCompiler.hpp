#ifndef PROGRAM_COMPILER_HPP
#define PROGRAM_COMPILER_HPP

#include "CompilerNode.hpp"

class ProgramCompiler : public CompilerNode {
public:
	~ProgramCompiler();
	bool parse();
	bool compile();
};

#endif