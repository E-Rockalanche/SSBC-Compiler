#ifndef LITERAL_COMPILER_HPP
#define LITERAL_COMPILER_HPP

#include "CompilerNode.hpp"

class LiteralCompiler : public CompilerNode {
public:
	~LiteralCompiler();
	bool parse();
	bool compile();
	Type getType();
	int getValue();
};

#endif