#ifndef ASSIGNMENT_EXP_COMPILER_HPP
#define ASSIGNMENT_EXP_COMPILER_HPP

#include "BaseCompiler.hpp"

class AssignmentExpCompiler : public CompilerNode {
public:
	~AssignmentExpCompiler();
	bool parse();
	bool compile();
	Type getType();
};

#endif