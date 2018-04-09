#include "SwitchCaseCompiler.hpp"
#include "StatementCompiler.hpp"
#include "LiteralCompiler.hpp"

SwitchCaseCompiler::~SwitchCaseCompiler(){}

bool SwitchCaseCompiler::parse(){
	P_BEGIN
	switch(currentToken().type()){
		case CppLang::DEFAULT:
			incIndex();
			defaultCase = true;
			P_EXPECT_TOKEN(CppLang::COLON);
			P_LOOP_NODE(new StatementCompiler())
			break;
		case CppLang::CASE:
			incIndex();
			defaultCase = false;
			P_ADD_NODE(new LiteralCompiler())
			P_EXPECT_TOKEN(CppLang::COLON);
			P_LOOP_NODE(new StatementCompiler())
			break;
		default:
			P_FAIL
	}
	P_END
}

bool SwitchCaseCompiler::compile(){
	dout("Compiling in " << __FILE__);

	unsigned int startIndex = 0;
	if (!defaultCase){
		assert(children.size() >= 1, "No case statement");
		startIndex = 1;
	}

	for(unsigned int i = startIndex; i < children.size(); i++){
		children[i]->compile();
	}

	return true;
}

int SwitchCaseCompiler::getValue(){
	assert(!defaultCase, "Cannot get value of default case");
	//return value of constant
	return children[0]->getValue();
}

bool SwitchCaseCompiler::isDefaultCase(){
	return defaultCase;
}