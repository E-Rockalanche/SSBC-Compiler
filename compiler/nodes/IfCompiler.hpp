#ifndef IF_COMPILER_HPP
#define IF_COMPILER_HPP

#include "BaseCompiler.hpp"

class IfCompiler : public CompilerNode {
public:
	~IfCompiler();
	bool parse();
	bool compile();
};

#endif