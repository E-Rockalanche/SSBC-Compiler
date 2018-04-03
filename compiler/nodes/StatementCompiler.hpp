#ifndef STATEMENT_COMPILER_HPP
#define STATEMENT_COMPILER_HPP

#include "BaseCompiler.hpp"

class StatementCompiler : public CompilerNode {
public:
	~StatementCompiler();
	bool parse();
	bool compile();
};

#endif