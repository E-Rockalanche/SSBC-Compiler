#ifndef BREAK_COMPILER_HPP
#define BREAK_COMPILER_HPP

#include "BaseCompiler.hpp"

class BreakCompiler : public CompilerNode {
public:
	~BreakCompiler();
	bool parse();
	bool compile();
	bool endsStatementSequence();
};

#endif