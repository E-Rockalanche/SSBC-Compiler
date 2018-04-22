#ifndef ARRAY_LITERAL_COMPILER_HPP
#define ARRAY_LITERAL_COMPILER_HPP

#include "BaseCompiler.hpp"

class ArrayLiteralCompiler : public CompilerNode {
public:
	~ArrayLiteralCompiler();
	bool parse();
	bool compile();
	void setElementType(Type type);
	Type getType();
private:
	Type elementType;
};

#endif