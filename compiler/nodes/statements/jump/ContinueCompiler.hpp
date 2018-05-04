#ifndef CONTINUE_COMPILER_HPP
#define CONTINUE_COMPILER_HPP

#include "CompilerNode.hpp"

class ContinueCompiler : public CompilerNode {
public:
	~ContinueCompiler();
	bool parse();
	bool compile();
	bool endsStatementSequence();
};

#endif