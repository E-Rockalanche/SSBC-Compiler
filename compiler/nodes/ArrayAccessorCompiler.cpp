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

	if (!varType.isPointer()){
		printError("Cannot use array accessor on non-pointer type",
			startTokenIndex);
		return false;
	}
	unsigned int derefSize = typeManager.sizeOf(varType.dereference());

	if (!children[0]->compile()) return false;
	if (!children[1]->compile()) return false;
	
	TypeConversionCompiler::convert(expType, Type("long"));
	string lowByte = newLabel();
	writeAssembly("jsr ADD16");
	writeAssembly("popext16 " + lowByte);
	writeAssembly("pushext ? " + lowByte + ": .word 0");
	if (derefSize == 2){
		string highByte = newLabel();
		writeAssembly("pushext16 " + lowByte);
		writeAssembly("pushimm16 1");
		writeAssembly("jsr ADD16");
		writeAssembly("popext16 " + highByte);
		writeAssembly("pushext ? " + highByte + ": .word 0");
	}

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
	return t.dereference();
}