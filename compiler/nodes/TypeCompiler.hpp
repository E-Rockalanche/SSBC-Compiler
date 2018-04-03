#ifndef TYPE_COMPILER_HPP
#define TYPE_COMPILER_HPP

#include "baseCompiler.hpp"

class TypeCompiler : public CompilerNode {
public:
	~TypeCompiler();
	bool parse();
	bool compile();
};

#endif