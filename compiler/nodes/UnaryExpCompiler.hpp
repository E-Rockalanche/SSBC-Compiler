#ifndef UNARY_EXP_COMPILER_HPP
#define UNARY_EXP_COMPILER_HPP

#include "BaseCompiler.hpp"

class UnaryExpCompiler : public CompilerNode {
public:
	~UnaryExpCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif