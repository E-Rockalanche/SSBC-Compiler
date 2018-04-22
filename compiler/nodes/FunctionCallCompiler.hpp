#ifndef FUNCTION_CALL_COMPILER_HPP
#define FUNCTION_CALL_COMPILER_HPP

#include "CompilerNode.hpp"

class FunctionCallCompiler : public CompilerNode {
public:
	~FunctionCallCompiler();
	bool parse();
	bool compile();
	Type getType();
	FunctionSignature getFunctionSignature();
private:
	Token identifier;
};

#endif