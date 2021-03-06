#ifndef PARAMETER_COMPILER_HPP
#define PARAMETER_COMPILER_HPP

#include "BaseCompiler.hpp"

class ParameterCompiler : public CompilerNode {
public:
	~ParameterCompiler();
	bool parse();
	Type getType();
	string getName();
private:
	Token identifier;
};

#endif