#ifndef FOR_LOOP_COMPILER_HPP
#define FOR_LOOP_COMPILER_HPP

#include "BaseCompiler.hpp"

class ForLoopCompiler : public CompilerNode {
public:
	~ForLoopCompiler();
	bool parse();
	bool compile();
};

#endif