#ifndef TYPE_COMPILER_HPP
#define TYPE_COMPILER_HPP

#include "CompilerNode.hpp"

class TypeCompiler : public CompilerNode {
public:
	~TypeCompiler();
	bool parse();
	bool compile();
};

#endif