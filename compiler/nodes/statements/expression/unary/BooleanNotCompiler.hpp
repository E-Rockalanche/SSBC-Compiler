#ifndef BOOLEAN_NOT_COMPILER_HPP
#define BOOLEAN_NOT_COMPILER_HPP

#include "CompilerNode.hpp"

class BooleanNotCompiler : public CompilerNode {
public:
	~BooleanNotCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif