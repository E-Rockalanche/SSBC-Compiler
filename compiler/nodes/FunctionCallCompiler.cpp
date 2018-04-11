#include "FunctionCallCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

FunctionCallCompiler::~FunctionCallCompiler(){}

bool FunctionCallCompiler::parse(){
	P_BEGIN
	if (currentToken().type() == CppLang::IDENTIFIER){
		identifier = currentToken();
		incIndex();
		//parameters
		P_EXPECT_TOKEN(CppLang::OPEN_PAREN);
		//optional first parameter
		CompilerNode* first = new ExpressionCompiler();
		if (first->parse()){
			children.push_back(first);
			while(currentToken().type() == CppLang::COMMA){
				incIndex();
				//required parameter for every expression
				P_ADD_NODE(new ExpressionCompiler())
			}
		}else{
			delete first;
		}
		P_EXPECT_TOKEN(CppLang::CLOSE_PAREN);
		P_END
	}
	P_FAIL
}

bool FunctionCallCompiler::compile(){
	dout("Compiling in " << __FILE__);

	FunctionSignature function = getFunctionSignature();
	if (!function.isDefined()){
		return false;
	}

	if (function == FunctionSignature("main", Type("void"))){
		printError("Canot call function main()");
		return false;
	}

	unsigned int scopeSize = 0;
	if(!inMain){
		//save scope
		writeComment("Saving local scope");
		vector<Type> scope = scopeTable.getScopeTypes();
		for(unsigned int i = 0; i < scope.size(); i++){
			scopeSize += typeManager.sizeOf(scope[i]);
		}
		dout("current scope size = " << scopeSize);

		assert(scopeSize <= SSBC_INT_MAX, "scope size greater than "
			+ to_string(SSBC_INT_MAX) + " not supported");

		if (scopeSize > 0){
			if (scopeSize <= 6){
				for(int i = scopeSize-1; i >= 0; i--){
					writeAssembly("pushext " + functionDataLabel + " + "
						+ to_string(i));
				}
			}else{
				writeAssembly("pushimm16 " + functionDataLabel);
				writeAssembly("pushimm " + to_string(scopeSize));
				writeAssembly("jsr PUSH_FROM_ADDR");
			}
		}
	}

	//compile arguments
	writeComment("Compiling function arguments");
	for(unsigned int i = 0; i < children.size(); i++){
		children[i]->compile();
		Type argType = children[i]->getType();
		TypeConversionCompiler::convert(argType, function.getParamType(i));
	}

	writeAssembly("jsr " + function.toLabel());

	if (!inMain){
		//save return value to temp location
		writeComment("saving return value to temp location");
		unsigned int returnTypeSize = typeManager.sizeOf(getType());
		string returnTempLabel = newLabel();
		if (returnTypeSize == 1){
			writeData(returnTempLabel + ": .byte 0");
			writeAssembly("popext " + returnTempLabel);
		}else{
			writeData(returnTempLabel + ": .word 0");
			writeAssembly("popext16 " + returnTempLabel);
		}

		//restore scope
		if (scopeSize > 0){
			if (scopeSize <= 6){
				for(unsigned int i = 0; i < scopeSize; i++){
					writeAssembly("popext " + functionDataLabel + " + "
						+ to_string(i));
				}
			}else{
				writeComment("Restoring scope");
				writeAssembly("pushimm16 " + functionDataLabel);
				writeAssembly("pushimm " + to_string(scopeSize));
				writeAssembly("jsr POP_TO_ADDR");
			}
		}

		//push return value to stack
		writeComment("Restoring return value from temp location");
		if (returnTypeSize == 1){
			writeAssembly("pushext " + returnTempLabel);
		}else{
			writeAssembly("pushext16 " + returnTempLabel);
		}
	}
	return true;
}

FunctionSignature FunctionCallCompiler::getFunctionSignature(){
	FunctionSignature callSig(identifier.value());
	for(unsigned int i = 0; i < children.size(); i++){
		callSig.addParameter(children[i]->getType());
	}
	FunctionSignature function = functionManager.findMatch(callSig);
	if (!function.isDefined()){
		printError("function " + callSig.toString() + " is not defined",
			startTokenIndex);
	}
	return function;
}

Type FunctionCallCompiler::getType(){
	FunctionSignature function = getFunctionSignature();
	if (function.isDefined()){
		return function.getReturnType();
	}else{
		return Type();
	}
}