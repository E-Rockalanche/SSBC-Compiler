#ifndef STATEMENT_SEQUENCE_COMPILER_HPP
#define STATEMENT_SEQUENCE_COMPILER_HPP

#include "BaseCompiler.hpp"

class StatementSequenceCompiler : public CompilerNode {
public:
	~StatementSequenceCompiler();
	bool parse();
	bool compile();
};

#endif