#include "ExitCompiler.hpp"

ExitCompiler::~ExitCompiler(){}

bool ExitCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::EXIT)
	P_END
}

bool ExitCompiler::compile(){
	dout("Compiling in " << __FILE__);
	writeAssembly("halt");
	returns = true;
	return true;
}

bool ExitCompiler::endsStatementSequence(){
	return true;
}