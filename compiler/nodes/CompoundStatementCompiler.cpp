#include "CompoundStatementCompiler.hpp"
#include "StatementSequenceCompiler.hpp"

CompoundStatementCompiler::~CompoundStatementCompiler(){}

bool CompoundStatementCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::OPEN_BRACE)
	P_ADD_NODE(new StatementSequenceCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_BRACE)
	P_END
}

bool CompoundStatementCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(children.size() == 1, "no compound statement");

	scopeTable.pushScope();

	bool ok = children.back()->compile();
	returns = children.back()->returnsFromFunction();
	endsSequence = children.back()->endsStatementSequence();

	scopeTable.popScope();

	return ok;
}