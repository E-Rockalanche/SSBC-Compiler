#ifndef BASE_COMPILER_NODE_HPP
#define BASE_COMPILER_NODE_HPP

#include "../BaseCompiler.hpp"

class BaseCompilerNode : public BaseCompiler {
public:
	virtual ~BaseCompilerNode();
	virtual bool parse();
	virtual bool compile();
	unsigned int getIndex();
	void setIndex(unsigned int startIndex);

protected:
	vector<CompilerNode*> children;

private:
	unsigned int startTokenIndex;
};

#endif