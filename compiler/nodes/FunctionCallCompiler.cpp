#include "FunctionCallCompiler.hpp"
#include "ArgumentsCompiler.hpp"

FunctionCallCompiler::~FunctionCallCompiler(){}

bool FunctionCallCompiler::parse(){
	P_BEGIN
	if (currentToken().type() == CppLang::IDENTIFIER){
		identifier = currentToken();
		incIndex();
		P_ADD_NODE(new ArgumentsCompiler())
		P_END
	}
	P_FAIL
}

bool FunctionCallCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No function call expression");
	if (getType().isDefined()){
		if (!children.back()->compile()) return false;
		writeAssembly("jsr " + getFunctionSignature().toLabel());
		return true;
	}else{
		printError("Function is not defined", startTokenIndex);
		return false;
	}
}

FunctionSignature FunctionCallCompiler::getFunctionSignature(){
	FunctionSignature function(identifier.value());
	((ArgumentsCompiler*)(children.back()))->addParametersToSignature(function);
	return function;
}

Type FunctionCallCompiler::getType(){
	assert(children.size() > 0, "No function call expression");
	FunctionSignature function = getFunctionSignature();
	if (functionManager.functionExists(function)){
		return functionManager.getReturnType(function);
	}
	return Type();
}