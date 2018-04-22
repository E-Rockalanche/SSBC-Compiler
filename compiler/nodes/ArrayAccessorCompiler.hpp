#ifndef ARRAY_ACCESSOR_COMPILER_HPP
#define ARRAY_ACCESSOR_COMPILER_HPP

#include "CompilerNode.hpp"

class ArrayAccessorCompiler : public CompilerNode {
public:
	~ArrayAccessorCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif