#ifndef EXIT_COMPILER_HPP
#define EXIT_COMPILER_HPP

#include "BaseCompiler.hpp"

class ExitCompiler : public CompilerNode {
public:
	~ExitCompiler();
	bool parse();
	bool compile();
	bool endsStatementSequence();
};

#endif