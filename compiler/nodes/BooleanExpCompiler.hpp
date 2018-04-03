#ifndef BOOLEAN_EXP_COMPILER_HPP
#define BOOLEAN_EXP_COMPILER_HPP

#include "BaseCompiler.hpp"

class BooleanExpCompiler : public CompilerNode {
public:
	~BooleanExpCompiler();
	bool parse();
	bool compile();
	Type getType();
private:
	Token token;
};

#endif