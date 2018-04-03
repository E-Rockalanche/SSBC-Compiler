#ifndef STRING_COMPILER_HPP
#define STRING_COMPILER_HPP

#include "BaseCompiler.hpp"

class StringCompiler : public CompilerNode {
public:
	~StringCompiler();
	bool parse();
	bool compile();
private:
	Token token;
};

#endif