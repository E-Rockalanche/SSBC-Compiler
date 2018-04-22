#ifndef GLOBAL_STATEMENT_COMPILER_HPP
#define GLOBAL_STATEMENT_COMPILER_HPP

#include "BaseCompiler.hpp"

class GlobalStatementCompiler : public CompilerNode {
public:
	~GlobalStatementCompiler();
	bool parse();
	bool compile();
};

#endif