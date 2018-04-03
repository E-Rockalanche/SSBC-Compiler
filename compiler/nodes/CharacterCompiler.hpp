#ifndef CHARACTER_COMPILER_HPP
#define CHARACTER_COMPILER_HPP

#include "BaseCompiler.hpp"

class CharacterCompiler : public CompilerNode {
public:
	~CharacterCompiler();
	bool parse();
	bool compile();
private:
	Token token;
};

#endif