#ifndef ADDITIVE_EXP_COMPILER_HPP
#define ADDITIVE_EXP_COMPILER_HPP

#include "BaseCompiler.hpp"

class AdditiveExpCompiler : public CompilerNode {
public:
	~AdditiveExpCompiler();
	bool parse();
	bool compile();
	Type getType();
private:
	Token token;
};

#endif