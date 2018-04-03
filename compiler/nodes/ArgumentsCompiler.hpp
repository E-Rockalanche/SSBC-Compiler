#ifndef ARGUMENTS_COMPILER_HPP
#define ARGUMENTS_COMPILER_HPP

#include "BaseCompiler.hpp"
#include "FunctionSignature.hpp"

class ArgumentsCompiler : public CompilerNode {
public:
	~ArgumentsCompiler();
	bool parse();
	bool compile();
	Type getType();
	bool addParametersToSignature(FunctionSignature& function);
};

#endif