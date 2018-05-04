#ifndef IF_ELSE_COMPILER_HPP
#define IF_ELSE_COMPILER_HPP

#include "../BaseStatementCompiler.hpp"

class IfElseCompiler : public BaseStatementCompiler {
public:
	~IfElseCompiler();
	bool parse();
	bool compile();
	bool returnsFromFunction();
	bool endsSequenceStatement();
};

#endif