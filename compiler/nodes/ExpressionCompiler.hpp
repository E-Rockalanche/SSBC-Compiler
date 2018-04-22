#ifndef EXPRESSION_COMPILER_HPP
#define EXPRESSION_COMPILER_HPP

#include "CompilerNode.hpp"

class ExpressionCompiler : public CompilerNode {
public:
	~ExpressionCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif