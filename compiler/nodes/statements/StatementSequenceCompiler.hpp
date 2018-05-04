#ifndef STATEMENT_SEQUENCE_COMPILER_HPP
#define STATEMENT_SEQUENCE_COMPILER_HPP

#include "BaseStatementCompiler.hpp"

class StatementSequenceCompiler : public BaseStatementCompiler {
public:
	~StatementSequenceCompiler();
	bool parse();
	bool compile();

	bool endsStatementSequence();
	bool returnsFromFunction();
};

#endif