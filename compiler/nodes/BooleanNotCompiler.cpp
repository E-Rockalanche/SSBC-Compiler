#include "BooleanNotCompiler.hpp"
#include "UnaryExpCompiler.hpp"

BooleanNotCompiler::~BooleanNotCompiler(){}

bool BooleanNotCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::NOT)
	P_ADD_NODE(new UnaryExpCompiler())
	P_END
}

bool BooleanNotCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No unary expression");
	writeComment("!");
	
	Type t = getType();
	int size = typeManager.sizeOf(t);
	if (size == 0){
		printError("Cannot perform boolean not operator on void type",
			startTokenIndex);
		return false;
	}else if (!typeManager.isPrimitive(t) && !t.isPointer()){
		printError("Cannot perform boolean not on non-primitive type",
			startTokenIndex);
		return false;
	}
	
	children.back()->compile();
	string trueLabel, endLabel;
	switch(size){
		case 1:
			trueLabel = newLabel();
			endLabel = newLabel();
			writeAssembly("test jnz " + trueLabel);
			writeAssembly("popinh pushimm 1 jump " + endLabel);
			writeAssembly(trueLabel + ": popinh pushimm 0");
			writeAssembly(endLabel + ":");
			break;
		default:
			printError("Cannot perform bitwise operator on size greater then 1 byte",
				startTokenIndex);
			return false;
	}

	writeComment("End !");
	return true;
}

Type BooleanNotCompiler::getType(){
	assert(children.size() > 0, "No unary expression");
	return children.back()->getType();
}