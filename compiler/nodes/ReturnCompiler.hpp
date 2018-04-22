#ifndef RETURN_COMPILER_HPP
#define RETURN_COMPILER_HPP

#include "CompilerNode.hpp"

class ReturnCompiler : public CompilerNode {
public:
	~ReturnCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif