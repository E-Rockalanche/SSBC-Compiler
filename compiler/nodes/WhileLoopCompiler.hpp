#ifndef WHILE_LOOP_COMPILER_HPP
#define WHILE_LOOP_COMPILER_HPP

#include "BaseCompiler.hpp"

class WhileLoopCompiler : public CompilerNode {
public:
	~WhileLoopCompiler();
	bool parse();
	bool compile();
};

#endif