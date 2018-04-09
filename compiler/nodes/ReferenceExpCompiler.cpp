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

	if (getType().isDefined()){
		writeAssembly("pushimm16 " + identifier.value());
		return true;
	}else{
		return false;
	}
}

Type ReferenceExpCompiler::getType(){
	Type type = scopeTable.getType(identifier.value());
	if (type.isDefined()){
		return type.addPointer();
	}else{
		printError(identifier.value() + " is undefined", getIndex() + 1);
	}
	return type;
}