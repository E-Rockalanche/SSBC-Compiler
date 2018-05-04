#ifndef ENCLOSED_EXP_COMPILER_HPP
#define ENCLOSED_EXP_COMPILER_HPP

#include "CompilerNode.hpp"

class EnclosedExpCompiler : public CompilerNode {
public:
	~EnclosedExpCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif