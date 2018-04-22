#ifndef SWITCH_CASE_COMPILER_HPP
#define SWITCH_CASE_COMPILER_HPP

#include "CompilerNode.hpp"
#include <string>
using namespace std;

class SwitchCaseCompiler : public CompilerNode {
public:
	~SwitchCaseCompiler();
	bool parse();
	bool compile();
	bool isDefaultCase();
	int getValue();
private:
	bool defaultCase;
};

#endif