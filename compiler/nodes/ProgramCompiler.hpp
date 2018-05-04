#ifndef PROGRAM_COMPILER_HPP
#define PROGRAM_COMPILER_HPP

#include "BaseCompilerNode.hpp"

class ProgramCompiler : public BaseCompilerNode {
public:
	~ProgramCompiler();
	bool parse();
	bool compile();
};

#endif