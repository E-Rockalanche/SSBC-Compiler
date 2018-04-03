#include "VariableExpCompiler.hpp"

VariableExpCompiler::~VariableExpCompiler(){}

bool VariableExpCompiler::parse(){
	P_BEGIN
	if (currentToken().type() == CppLang::IDENTIFIER){
		identifier = currentToken();
		incIndex();
		P_END
	}
	P_FAIL
}

bool VariableExpCompiler::compile(){
	dout("Compiling in " << __FILE__);

	type = getType();
	if (type.isDefined()){
		int size = typeManager.sizeOf(type);
		for(int i = size-1; i >= 0; i--){
			writeAssembly("pushext " + identifier.value() + " + "
				+ to_string(i));
		}
		return true;
	}else{
		printError("Variable " + identifier.value() + " is not defined",
			startTokenIndex);
		return false;
	}
}

Type VariableExpCompiler::getType(){
	if (!type.isDefined()){
		type = scopeTable.getType(identifier.value());
	}
	return type;
}