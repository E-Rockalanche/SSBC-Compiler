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

bool VariableExpCompiler::compile() {
	dout("Compiling in " << __FILE__);

	string label = scopeTable.getLabel(identifier.value());

	//cannot use getType() since getType() dereferences type
	Type type = scopeTable.getType(identifier.value());

	if (type.isDefined()){
		unsigned int size = typeManager.sizeOf(type);

		if (type.isReference()) {
			writeAssembly("pushext16 " + label);
			pushFromAddress(size);
		} else if (type.isArray()) {
			writeAssembly("pushimm16 " + label);
		} else {
			pushFromAddress(label, size);
		}
		return true;
	}
	return false;
}

Type VariableExpCompiler::getType() {
	if (!type.isDefined()) {
		type = scopeTable.getType(identifier.value());
		
		if (!type.isDefined()) {
			printError("Variable " + identifier.value() + " is not defined",
				startTokenIndex);
		} else if (type.isReference()) {
			type.dereference();
		} else if (type.isArray()) {
			type.convertArrayToPointer();
		}
	}
	return type;
}