#include "VariableAssignmentCompiler.hpp"

VariableAssignmentCompiler::~VariableAssignmentCompiler(){}

bool VariableAssignmentCompiler::parse(){
	P_BEGIN
	if (currentToken().type() == CppLang::IDENTIFIER){
		identifier = currentToken();
		incIndex();
		P_END
	}
	P_FAIL
}

bool VariableAssignmentCompiler::compile(){
	dout("Compiling in " << __FILE__);
	
	type = getType();
	if (type.isDefined()){
		unsigned int size = typeManager.sizeOf(type);
		for(unsigned int i = 0; i < size; i++){
			writeAssembly("popext " + identifier.value() + " + " + to_string(i));
		}
		return true;
	}else{
		printError("Variable " + identifier.value() + " is undefined",
			startTokenIndex);
	}
	return false;
}

Type VariableAssignmentCompiler::getType(){
	if (!type.isDefined()){
		if (scopeTable.isDefined(identifier.value())){
			type = scopeTable.getType(identifier.value());
		}
	}
	return type;
}