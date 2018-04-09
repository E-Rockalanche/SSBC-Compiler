#ifndef REFERENCE_EXP_COMPILER_HPP
#define REFERENCE_EXP_COMPILER_HPP

#include "BaseCompiler.hpp"

class ReferenceExpCompiler : public CompilerNode {
public:
	~ReferenceExpCompiler();
	bool parse();
	bool compile();
	Type getType();
private:
	Token identifier;
};

#endif