#include "VariableDefCompiler.hpp"
#include "TypeCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"
#include "TypeManager.hpp"

VariableDefCompiler::~VariableDefCompiler(){}

bool VariableDefCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new TypeCompiler())
	P_EXPECT_TOKEN_SET(CppLang::IDENTIFIER, identifier = currentToken(), )
	P_OPTIONAL_TOKEN_SET(CppLang::ASSIGN, ,
		P_ADD_NODE(new ExpressionCompiler())
	)
	P_END
}

bool VariableDefCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(children.size() > 0, "No variable definition");

	Type type = children[0]->getType();
	string typeName = type.getBaseType();
	if (!typeManager.typeExists(typeName)){
		printError("Type " + typeName + " is not defined",
			children[0]->getIndex());
		return false;
	}

	if (type.isArray()) {
		int arraySize = type.getArraySize();
		if (arraySize <= 0) {
			printError("Invalid array size", children[0]->getIndex());
			return false;
		} else if (arraySize > (SSBC_PTR_MAX + 1)) {
			printError("Array size must be " + to_string(SSBC_PTR_MAX + 1)
				+ " or less");
			return false;
		}
	}

	if (typeManager.typeExists(identifier.value())){
		printError("Cannot define variable with type name "
			+ identifier.value());
		return false;
	}

	string label = newLabel();
	unsigned int typeSize = typeManager.sizeOf(type);
	scopeTable.add(identifier.value(), type, label, typeSize);

	if (children.size() == 2){
		//compile assignment
		children[1]->compile();
		Type from = children[1]->getType();
		TypeConversionCompiler::convert(from, type, getIndex());
		popToAddress(label, typeManager.sizeOf(type));
	}
	
	#if(DEBUG)
		scopeTable.dump();
	#endif
	
	return true;
}