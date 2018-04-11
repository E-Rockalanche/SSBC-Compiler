#ifndef FUNCTION_CALL_STMT_COMPILER_HPP
#define FUNCTION_CALL_STMT_COMPILER_HPP

#include "BaseCompiler.hpp"

class FunctionCallStmtCompiler : public CompilerNode {
public:
	~FunctionCallStmtCompiler();
	bool parse();
	bool compile();
};

#endif