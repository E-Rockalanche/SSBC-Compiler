#ifndef VARIABLE_DEF_COMPILER_HPP
#define VARIABLE_DEF_COMPILER_HPP

#include "BaseCompiler.hpp"

class VariableDefCompiler : public CompilerNode {
public:
	~VariableDefCompiler();
	bool parse();
	bool compile();
private:
	Token  identifier;
};

#endif