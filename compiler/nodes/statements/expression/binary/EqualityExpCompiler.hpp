#ifndef EQUALITY_EXP_COMPILER_HPP
#define EQUALITY_EXP_COMPILER_HPP

#include "CompilerNode.hpp"

class EqualityExpCompiler : public CompilerNode {
public:
	~EqualityExpCompiler();
	bool parse();
	bool compile();
	Type getType();
private:
	Token token;
};

#endif