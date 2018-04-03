#include "BitwiseNotCompiler.hpp"
#include "UnaryExpCompiler.hpp"

BitwiseNotCompiler::~BitwiseNotCompiler(){}

bool BitwiseNotCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::TILDE)
	P_ADD_NODE(new UnaryExpCompiler())
	P_END
}

bool BitwiseNotCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No unary expression");
	writeComment("Bitwise not");

	Type t = getType();
	int size = typeManager.sizeOf(t);
	if (size == 0){
		printError("Cannot perform bitwise not operator on void type",
			startTokenIndex);
		return false;
	}else if (t.isPointer()){
		printWarning("Bitwise expression on pointer",
			startTokenIndex);
	}else if (!typeManager.isPrimitive(t)){
		printError("Cannot perform bitwise not on non-primitive type",
			startTokenIndex);
		return false;
	}
	
	children.back()->compile();
	switch(size){
		case 1:
			writeAssembly("not");
			break;
		default:
			printError("Cannot perform bitwise operator on size greater then 1 byte",
				startTokenIndex);
			return false;
	}

	writeComment("End bitwise not");
	return true;
}

Type BitwiseNotCompiler::getType(){
	assert(children.size() > 0, "No unary expression");
	return children.back()->getType();
}