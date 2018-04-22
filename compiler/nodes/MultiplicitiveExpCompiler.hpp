#ifndef MULTIPLICITIVE_EXP_COMPILER_HPP
#define MULTIPLICITIVE_EXP_COMPILER_HPP

#include "CompilerNode.hpp"

class MultiplicitiveExpCompiler : public CompilerNode {
public:
	~MultiplicitiveExpCompiler();
	bool parse();
	bool compile();
	Type getType();
private:
	Token token;
};

#endif