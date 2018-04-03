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

	unsigned int derefSize = typeManager.sizeOf(t.dereference());
	if (derefSize > 2 || derefSize == 0){
		printError("Cannot dereference to type " + t.toString(),
			startTokenIndex);
		return false;
	}
	
	if (!children.back()->compile()) return false;

	string lowByte = newLabel();
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
	return t.dereference();
}