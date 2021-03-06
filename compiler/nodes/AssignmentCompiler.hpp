#ifndef ASSIGNMENT_COMPILER_HPP
#define ASSIGNMENT_COMPILER_HPP

#include "BaseCompiler.hpp"

class AssignmentCompiler : public CompilerNode {
public:
	~AssignmentCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif