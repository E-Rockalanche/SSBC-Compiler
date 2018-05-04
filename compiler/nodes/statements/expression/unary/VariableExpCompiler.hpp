#ifndef VARIABLE_EXP_COMPILER_HPP
#define VARIABLE_EXP_COMPILER_HPP

#include "CompilerNode.hpp"

class VariableExpCompiler : public CompilerNode {
public:
	~VariableExpCompiler();
	bool parse();
	bool compile();
	Type getType();
private:
	Token identifier;
};

#endif