#include "ArrayAccessorCompiler.hpp"
#include "VariableExpCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

ArrayAccessorCompiler::~ArrayAccessorCompiler(){}

bool ArrayAccessorCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new VariableExpCompiler())
	P_EXPECT_TOKEN(CppLang::OPEN_BRACKET)
	P_ADD_NODE(new ExpressionCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_BRACKET)
	P_END
}

bool ArrayAccessorCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() == 2, "No array expression");
	writeComment("Array accessor");

	Type varType = children[0]->getType();
	Type expType = children[1]->getType();

	if (!(varType.isPointer() || varType.isArray())) {
		printError("Cannot use array accessor on type " + varType.toString(),
			startTokenIndex);
		return false;
	}
	unsigned int derefSize = typeManager.sizeOf(varType.removePointer());

	//push array pointer
	if (!children[0]->compile()) return false;

	//push expression value and convert to correct array offset
	if (!children[1]->compile()) return false;
	TypeConversionCompiler::convert(expType, Type("long"));
	if (derefSize > 1){
		writeComment("Calculate array offset");
		writeAssembly("pushimm16 " + to_string(derefSize));
		writeAssembly("jsr MULT16");
		writeComment("End Calculate array offset");
	}

	writeAssembly("jsr ADD16");
	writeAssembly("pushimm " + to_string(derefSize));
	writeAssembly("jsr PUSH_FROM_ADDR");

	writeComment("End array accessor");
	return true;
}

Type ArrayAccessorCompiler::getType(){
	assert(children.size() > 0, "No array accessor expression");
	Type t = children[0]->getType();
	if (!t.isPointer()){
		printError("Cannot dereference non-pointer type", startTokenIndex);
		return Type();
	}
	return t.removePointer();
}