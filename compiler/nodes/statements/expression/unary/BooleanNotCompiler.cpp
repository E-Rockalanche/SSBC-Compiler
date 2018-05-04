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
	
	Type t = children.back()->getType();
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
	string trueLabel = newLabel();
	string endLabel = newLabel();
	switch(size){
		case 1:
			writeAssembly("test popinh jnz " + trueLabel);
			break;
		case 2:
			writeAssembly("jsr TEST16 popext PSW popinh16 jnz " + trueLabel);
		default:
			printError("Cannot perform boolean not on type of size greater than 2 bytes",
				startTokenIndex);
			return false;
	}
	writeAssembly("pushimm 1 jump " + endLabel);
	writeAssembly(trueLabel + ": pushimm 0");
	writeAssembly(endLabel + ":");

	writeComment("End !");
	return true;
}

Type BooleanNotCompiler::getType(){
	assert(children.size() > 0, "No unary expression");
	return Type("bool");
}