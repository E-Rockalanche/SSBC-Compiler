#ifndef BOOLEAN_NOT_COMPILER_HPP
#define BOOLEAN_NOT_COMPILER_HPP

#include "BaseCompiler.hpp"

class BooleanNotCompiler : public CompilerNode {
public:
	~BooleanNotCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif