#ifndef STATEMENT_SEQUENCE_COMPILER_HPP
#define STATEMENT_SEQUENCE_COMPILER_HPP

#include "CompilerNode.hpp"

class StatementSequenceCompiler : public CompilerNode {
public:
	~StatementSequenceCompiler();
	bool parse();
	bool compile();
};

#endif