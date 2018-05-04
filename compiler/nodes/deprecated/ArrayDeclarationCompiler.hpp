#ifndef ARRAY_DECLARATION_COMPILER_HPP
#define ARRAY_DECLARATION_COMPILER_HPP

#include "CompilerNode.hpp"

class ArrayDeclarationCompiler : public CompilerNode {
public:
	~ArrayDeclarationCompiler();
	bool parse();
	bool compile();
	int getValue();
};

#endif