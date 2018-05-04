#ifndef FUNCTION_DEF_COMPILER_HPP
#define FUNCTION_DEF_COMPILER_HPP

#include "CompilerNode.hpp"
#include "FunctionSignature.hpp"
#include <string>
using namespace std;

class FunctionDefCompiler : public CompilerNode {
public:
	~FunctionDefCompiler();
	bool parse();
	bool compile();

private:
	FunctionSignature mySignature;
	string returnAddrLabel;

	void setStaticData();
	void compileFunctionStart();
	void compileArguments();
	void compileFunctionEnd();
	void compileLocalMemory();
};

#endif