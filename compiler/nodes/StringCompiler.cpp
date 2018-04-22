#include "StringCompiler.hpp"

StringCompiler::~StringCompiler(){}

bool StringCompiler::parse(){
	if (currentToken().type() == CppLang::STRING){
		token = currentToken();
		type = Type("char", true).addPointer();
		incIndex();
		return true;
	}else{
		return false;
	}
}

bool StringCompiler::compile(){
	dout("Compiling in " << __FILE__);

	string label = newLabel();
	writeGlobalData(label + ": .asciz " + token.value());
	writeAssembly("pushimm16 " + label);
	return true;
}