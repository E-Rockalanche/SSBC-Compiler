#include "VariableDefCompiler.hpp"
#include "TypeCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

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
		printError("Type " + typeName + " is not defined", startTokenIndex);
		return false;
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