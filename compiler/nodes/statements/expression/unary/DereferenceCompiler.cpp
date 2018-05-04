#include "DereferenceCompiler.hpp"
#include "UnaryExpCompiler.hpp"

DereferenceCompiler::~DereferenceCompiler(){}

bool DereferenceCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::ASTERISK)
	P_ADD_NODE(new UnaryExpCompiler())
	P_END
}

bool DereferenceCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No unary expression");
	writeComment("Dereference");

	Type t = children.back()->getType();
	if (!t.isPointer()){
		printError("Cannot dereference a non-pointer type",
			startTokenIndex);
		return false;
	}

	Type tCopy = t;

	unsigned int derefSize = typeManager.sizeOf(t.removePointer());
	if (derefSize == 0){
		printError("Cannot dereference type " + tCopy.toString(),
			startTokenIndex);
		return false;
	}
	
	if (!children.back()->compile()) return false;

	writeAssembly("pushimm " + to_string(derefSize));
	writeAssembly("jsr PUSH_FROM_ADDR");

	writeComment("End dereference");
	return true;
}

Type DereferenceCompiler::getType(){
	assert(children.size() > 0, "No dereference expression");
	Type t = children.back()->getType();
	if (!t.isPointer()){
		printError("Cannot dereference non-pointer type",
			startTokenIndex);
		return Type();
	}
	return t.removePointer();
}