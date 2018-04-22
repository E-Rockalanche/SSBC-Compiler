#ifndef COMPILER_NODE_HPP
#define COMPILER_NODE_HPP

#include "CompilerData.hpp"

class CompilerNode : public CompilerData {
public:
	virtual ~CompilerNode();
	virtual bool parse();
	virtual bool compile();
	unsigned int getIndex();

	//for expressions
	virtual Type getType();
	virtual int getValue();

	//for statements
	virtual bool endsStatementSequence();
	bool returnsFromFunction();

protected:
	unsigned int startTokenIndex;
	vector<CompilerNode*> children;
	Type type;
	bool returns = false;
	bool endsSequence = false;
};

#endif