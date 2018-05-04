#include "ArrayAssignmentCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"
#include "VariableExpCompiler.hpp"

ArrayAssignmentCompiler::~ArrayAssignmentCompiler(){}

bool ArrayAssignmentCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new VariableExpCompiler())
	P_EXPECT_TOKEN(CppLang::OPEN_BRACKET)
	P_ADD_NODE(new ExpressionCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_BRACKET)
	P_END
}

bool ArrayAssignmentCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No array expression");
	writeComment("Array assignment");

	type = getType();
	if (!type.isDefined()){
		return false;
	}

	children[0]->compile();

	children[1]->compile();
	TypeConversionCompiler::convert(children[1]->getType(),
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

	writeComment("End array assignment");
	return true;
}

Type ArrayAssignmentCompiler::getType(){
	assert(children.size() > 0, "No array expression");
	if (!type.isDefined()){
		Type t = children[0]->getType();
		if (t.isPointer()){
			type = t.removePointer();
		}else{
			printError("Cannot use array notation on non-pointer type",
				startTokenIndex);
			type = Type();
		}
	}
	return type;
}