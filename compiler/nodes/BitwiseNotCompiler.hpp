#ifndef BITWISE_NOT_COMPILER_HPP
#define BITWISE_NOT_COMPILER_HPP

#include "CompilerNode.hpp"

class BitwiseNotCompiler : public CompilerNode {
public:
	~BitwiseNotCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif