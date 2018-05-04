#ifndef VARIABLE_ASSIGNMENT_COMPILER_HPP
#define VARIABLE_ASSIGNMENT_COMPILER_HPP

#include "CompilerNode.hpp"

class VariableAssignmentCompiler : public CompilerNode {
public:
	~VariableAssignmentCompiler();
	bool parse();
	bool compile();
	Type getType();
	string getName();
private:
	Token identifier;
};

#endif