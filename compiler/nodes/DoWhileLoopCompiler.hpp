#ifndef DO_WHILE_LOOP_COMPILER_HPP
#define DO_WHILE_LOOP_COMPILER_HPP

#include "CompilerNode.hpp"

class DoWhileLoopCompiler : public CompilerNode {
public:
	~DoWhileLoopCompiler();
	bool parse();
	bool compile();
};

#endif