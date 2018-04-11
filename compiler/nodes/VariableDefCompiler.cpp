#include "VariableDefCompiler.hpp"
#include "TypeCompiler.hpp"
#include "ArrayDeclarationCompiler.hpp"

VariableDefCompiler::~VariableDefCompiler(){}

bool VariableDefCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new TypeCompiler())
	if (currentToken().type() == CppLang::IDENTIFIER){
		identifier = currentToken();
		incIndex();
		P_OPTIONAL_NODE(new ArrayDeclarationCompiler())
		P_END
	}
	P_FAIL
}

bool VariableDefCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No variable definition");
	Type type = children[0]->getType();
	if (children.size() == 2){
		type.addPointer();
	}

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

	string label = newLabel();
	scopeTable.add(identifier.value(), type, label);

	if (children.size() == 2){
		dout("assigning variable to array");
		//assign array pointer to variable
		unsigned int typeSize = typeManager.sizeOf(typeName);
		unsigned int arraySize = children[1]->getValue();
		string arrayLabel = newLabel();
		writeData(arrayLabel + ": .array " + to_string(arraySize * typeSize));
		writeAssembly("pushimm16 " + arrayLabel);
		writeAssembly("popext16 " + label);
	}
	
	#if(DEBUG)
		scopeTable.dump();
	#endif

	if (typeManager.sizeOf(type) == 1){
		writeScopeData(label + ": .byte 0");
	}else{

		writeScopeData(label + ": .word 0");
	}
	return true;
}