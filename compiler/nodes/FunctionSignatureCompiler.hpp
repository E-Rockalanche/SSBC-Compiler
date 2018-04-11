#ifndef FUNCTION_SIGNATURE_COMPILER_HPP
#define FUNCTION_SIGNATURE_COMPILER_HPP

#include "BaseCompiler.hpp"

class FunctionSignatureCompiler : public CompilerNode {
public:
	~FunctionSignatureCompiler();
	bool parse();
	FunctionSignature getSignature();
private:
	Token identifier;
};

#endif