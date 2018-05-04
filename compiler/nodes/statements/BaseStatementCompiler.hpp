#ifndef BASE_STATEMENT_COMPILER
#define BASE_STATEMENT_COMPILER

class BaseStatementCompiler : public BaseCompilerNode {
public:
	virtual bool parse() = 0;
	virtual bool compile() = 0;

	//for statements
	virtual bool endsStatementSequence();
	virtual bool returnsFromFunction();
};

#endif