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

	assert(type != Type("void"), "void type in VariableAssignmentCompiler");

	if (!type.isDefined()){
		printError("Variable " + identifier.value() + " is undefined",
			startTokenIndex);
		return false;
	}

	if(scopeTable.isDefined(identifier.value())){
		string label = scopeTable.getLabel(identifier.value());
		unsigned int size = typeManager.sizeOf(type);
		popToAddress(label, size);
		return true;
	}else{
		printError(identifier.value() + " is not defined");
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

string VariableAssignmentCompiler::getName(){
	return identifier.value();
}