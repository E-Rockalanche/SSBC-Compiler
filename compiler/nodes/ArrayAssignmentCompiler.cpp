#include "ArrayAssignmentCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

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

		children.back()->compile();
		TypeConversionCompiler::convert(children.back()->getType(),
			Type("long"));
		int derefSize = typeManager.sizeOf(type);

		if (derefSize > 1){
			writeComment("Calculate array offset");
			writeAssembly("pushimm16 " + to_string(derefSize));
			writeAssembly("jsr MULT16");
			writeComment("End Calculate array offset");
		}
		//calculate pointer
		writeAssembly("jsr ADD16");

		//pop data to pointer
		writeAssembly("pushimm " + to_string(derefSize));
		writeAssembly("jsr POP_TO_ADDR");
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