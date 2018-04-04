#include "VariableDefCompiler.hpp"
#include "TypeCompiler.hpp"

VariableDefCompiler::~VariableDefCompiler(){}

bool VariableDefCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new TypeCompiler())
	if (currentToken().type() == CppLang::IDENTIFIER){
		identifier = currentToken();
		incIndex();
		P_END
	}
	P_FAIL
}

bool VariableDefCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No variable definition");
	Type type = children.back()->getType();

	dout("type = " << type.toString());

	string typeName = type.getBaseType();

	if (!typeManager.typeExists(typeName)){
		printError("Type " + typeName + " is not defined", startTokenIndex);
		return false;
	}

	if (typeManager.typeExists(identifier.value())){
		printError("Cannot define variable with type name "
			+ identifier.value());
		return false;
	}

	scopeTable.add(identifier.value(), type);
	
	#if(DEBUG)
		scopeTable.dump();
	#endif

	if (typeManager.sizeOf(type) == 1){
		writeData(identifier.value() + ": .byte 0");
	}else{
		writeData(identifier.value() + ": .word 0");
	}
	return true;
}