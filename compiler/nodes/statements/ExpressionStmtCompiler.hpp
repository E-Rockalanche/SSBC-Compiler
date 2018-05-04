#ifndef EXPRESSION_STMT_COMPILER_HPP
#define EXPRESSION_STMT_COMPILER_HPP

#include "BaseStatementCompiler.hpp"

class ExpressionStmtCompiler : public BaseStatementCompiler {
public:
	~ExpresionStmtCompiler();
	bool parse();
	bool compile();
};

#endif