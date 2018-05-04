#include "BreakCompiler.hpp"

BreakCompiler::~BreakCompiler(){}

bool BreakCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::BREAK)
	P_END
}

bool BreakCompiler::compile(){
	dout("Compiling in " << __FILE__);
	if (breakManager.inScope()){
		string endLabel = breakManager.getEndLabel();
		writeComment("Break");
		writeAssembly("jump " + endLabel);
		return true;
	}else{
		printError("Cannot break from current scope", getIndex());
		return false;
	}
}

bool BreakCompiler::endsStatementSequence(){
	return true;
}