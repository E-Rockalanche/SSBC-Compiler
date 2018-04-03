#ifndef ARRAY_ASSIGNMENT_COMPILER_HPP
#define ARRAY_ASSIGNMENT_COMPILER_HPP

#include "BaseCompiler.hpp"

class ArrayAssignmentCompiler : public CompilerNode {
public:
	~ArrayAssignmentCompiler();
	bool parse();
	bool compile();
	Type getType();
private:
	Token identifier;
};

#endif