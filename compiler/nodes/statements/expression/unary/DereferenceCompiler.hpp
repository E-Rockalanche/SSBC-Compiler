#ifndef DEREFERENCE_COMPILER_HPP
#define DEREFERENCE_COMPILER_HPP

#include "CompilerNode.hpp"

class DereferenceCompiler : public CompilerNode {
public:
	~DereferenceCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif