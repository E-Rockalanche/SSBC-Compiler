#ifndef RELATIONAL_EXP_COMPILER_HPP
#define RELATIONAL_EXP_COMPILER_HPP

#include "CompilerNode.hpp"

class RelationalExpCompiler : public CompilerNode {
public:
	~RelationalExpCompiler();
	bool parse();
	bool compile();
	Type getType();
private:
	Token token;
};

#endif