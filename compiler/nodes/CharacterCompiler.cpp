#include "CharacterCompiler.hpp"

CharacterCompiler::~CharacterCompiler(){}

bool CharacterCompiler::parse(){
	if (currentToken().type() == CppLang::CHARACTER){
		token = currentToken();
		type = Type("char", true);
		incIndex();
		return true;
	}else{
		return false;
	}
}

bool CharacterCompiler::compile(){
	dout("Compiling in " << __FILE__);

	writeAssembly("pushimm " + token.value());
	return true;
}