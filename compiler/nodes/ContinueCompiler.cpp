#include "ContinueCompiler.hpp"

ContinueCompiler::~ContinueCompiler(){}

bool ContinueCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::CONTINUE)
	P_END
}

bool ContinueCompiler::compile(){
	dout("Compiling in " << __FILE__);
	if (breakManager.inLoop()){
		string startLabel = breakManager.getStartLabel();
		writeAssembly("jump " + startLabel);
		return true;
	}else{
		printError("Cannot continue outside of a loop", getIndex());
		return false;
	}
}