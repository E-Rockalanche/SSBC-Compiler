#include "SwitchCaseCompiler.hpp"
#include "StatementSequenceCompiler.hpp"
#include "LiteralCompiler.hpp"

SwitchCaseCompiler::~SwitchCaseCompiler(){}

bool SwitchCaseCompiler::parse(){
	P_BEGIN
	switch(currentToken().type()){
		case CppLang::DEFAULT:
			incIndex();
			defaultCase = true;
			P_EXPECT_TOKEN(CppLang::COLON);
			P_ADD_NODE(new StatementSequenceCompiler())
			break;
		case CppLang::CASE:
			incIndex();
			defaultCase = false;
			P_ADD_NODE(new LiteralCompiler())
			P_EXPECT_TOKEN(CppLang::COLON);
			P_ADD_NODE(new StatementSequenceCompiler())
			break;
		default:
			P_FAIL
	}
	P_END
}

bool SwitchCaseCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(children.size() >= 1, "No case statement");

	bool ok = children.back()->compile();
	returns = children.back()->returnsFromFunction();

	return ok;
}

int SwitchCaseCompiler::getValue(){
	assert(!defaultCase, "Cannot get value of default case");
	//return value of constant
	return children[0]->getValue();
}

bool SwitchCaseCompiler::isDefaultCase(){
	return defaultCase;
}