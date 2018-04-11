#ifndef RETURN_COMPILER_HPP
#define RETURN_COMPILER_HPP

#include "BaseCompiler.hpp"

class ReturnCompiler : public CompilerNode {
public:
	~ReturnCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif