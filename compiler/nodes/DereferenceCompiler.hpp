#ifndef DEREFERENCE_COMPILER_HPP
#define DEREFERENCE_COMPILER_HPP

#include "BaseCompiler.hpp"

class DereferenceCompiler : public CompilerNode {
public:
	~DereferenceCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif