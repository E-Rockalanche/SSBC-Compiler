#ifndef IF_ELSE_COMPILER_HPP
#define IF_ELSE_COMPILER_HPP

#include "BaseCompiler.hpp"

class IfElseCompiler : public CompilerNode {
public:
	~IfElseCompiler();
	bool parse();
	bool compile();
};

#endif