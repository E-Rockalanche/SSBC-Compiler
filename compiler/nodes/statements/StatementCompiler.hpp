#ifndef STATEMENT_COMPILER_HPP
#define STATEMENT_COMPILER_HPP

#include "BaseStatementCompiler.hpp"

class StatementCompiler : public BaseStatementCompiler {
public:
	~StatementCompiler();
	bool parse();
	bool compile();
	bool endsStatementSequence();
	bool returnsFromFunction();
};

#endif