#ifndef INTEGER_COMPILER_HPP
#define INTEGER_COMPILER_HPP

#include "BaseCompiler.hpp"

class IntegerCompiler : public CompilerNode {
public:
	~IntegerCompiler();
	bool parse();
	bool compile();
	int getValue();
private:
	int value;
};

#endif