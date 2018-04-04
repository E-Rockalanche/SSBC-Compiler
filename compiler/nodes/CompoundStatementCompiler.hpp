#ifndef COMPOUND_STATEMENT_COMPILER_HPP
#define COMPOUND_STATEMENT_COMPILER_HPP

#include "BaseCompiler.hpp"

class CompoundStatementCompiler : public CompilerNode {
public:
	~CompoundStatementCompiler();
	bool parse();
	bool compile();
};

#endif