#ifndef CONTINUE_COMPILER_HPP
#define CONTINUE_COMPILER_HPP

#include "BaseCompiler.hpp"

class ContinueCompiler : public CompilerNode {
public:
	~ContinueCompiler();
	bool parse();
	bool compile();
};

#endif