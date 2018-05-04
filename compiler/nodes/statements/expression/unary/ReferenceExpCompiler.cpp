#include "ReferenceExpCompiler.hpp"
#include "VariableExpCompiler.hpp"
#include "TypeConversionCompiler.hpp"

ReferenceExpCompiler::~ReferenceExpCompiler(){}

bool ReferenceExpCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::AMPERSAND)
	if (currentToken().type() == CppLang::IDENTIFIER){
		identifier = currentToken();
		incIndex();
		P_END
	}
	P_FAIL
}

bool ReferenceExpCompiler::compile(){
	dout("Compiling in " << __FILE__);

	Type type = getType();

	if (type.isDefined()){
		string label = scopeTable.getLabel(identifier.value());
		if (type.isReference()){
			writeAssembly("pushext16 " + label);
		} else {
			writeAssembly("pushimm16 " + label);
		}
		return true;
	}
	return false;
}

Type ReferenceExpCompiler::getType(){
	if (!type.isDefined()) {
		type = scopeTable.getType(identifier.value());
		if (type.isDefined()){
			type.addPointer();
		}else{
			printError(identifier.value() + " is undefined", getIndex() + 1);
		}
	}
	return type;
}