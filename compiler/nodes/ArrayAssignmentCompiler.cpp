#include "ArrayAssignmentCompiler.hpp"
#include "ExpressionCompiler.hpp"

ArrayAssignmentCompiler::~ArrayAssignmentCompiler(){}

bool ArrayAssignmentCompiler::parse(){
	P_BEGIN
	if (currentToken().type() == CppLang::IDENTIFIER){
		identifier = currentToken();
		incIndex();
		P_EXPECT_TOKEN(CppLang::OPEN_BRACKET)
		P_ADD_NODE(new ExpressionCompiler())
		P_EXPECT_TOKEN(CppLang::CLOSE_BRACKET)
		P_END
	}
	P_FAIL
}

bool ArrayAssignmentCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No array expression");
	writeComment("Array assignment");
	type = getType();
	if (type.isDefined()){
		writeAssembly("pushext16 " + identifier.value());
		if (!children.back()->compile()) return false;
		compileTypeConversion(children.back()->getType(), Type("long"));

		writeAssembly("jsr ADD16");
		string lowByte = newLabel();
		writeAssembly("popext16 " + lowByte);
		writeAssembly("popext ? " + lowByte + ": .word 0");
		if (typeManager.sizeOf(type) == 2){
			string highByte = newLabel();
			writeAssembly("pushext16 " + lowByte);
			writeAssembly("pushimm16 1");
			writeAssembly("jsr ADD16");
			writeAssembly("popext16 " + highByte);
			writeAssembly("popext ? " + highByte + ": .word 0");
		}
	}

	writeComment("End array assignment");
	return true;
}

Type ArrayAssignmentCompiler::getType(){
	assert(children.size() > 0, "No array expression");
	if (!type.isDefined()){
		Type t = scopeTable.getType(identifier.value());
		if (t.isPointer()){
			type = t.dereference();
		}else{
			printError("Variable " + identifier.value()
				+ " is not a pointer. It is of type " + t.toString(),
				startTokenIndex);
		}
	}
	return type;
}