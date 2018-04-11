#ifndef FUNCTION_DEF_COMPILER_HPP
#define FUNCTION_DEF_COMPILER_HPP

#include "BaseCompiler.hpp"

class FunctionDefCompiler : public CompilerNode {
public:
	~FunctionDefCompiler();
	bool parse();
	bool compile();
};

#endif