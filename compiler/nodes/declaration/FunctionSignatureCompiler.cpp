#include "FunctionSignatureCompiler.hpp"
#include "ParameterCompiler.hpp"
#include "TypeCompiler.hpp"

FunctionSignatureCompiler::~FunctionSignatureCompiler(){}

bool FunctionSignatureCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new TypeCompiler())
	if (currentToken().type() == CppLang::IDENTIFIER){
		identifier = currentToken();
		incIndex();

		P_EXPECT_TOKEN(CppLang::OPEN_PAREN)

		CompilerNode* first = new ParameterCompiler();
		if (first->parse()){
			children.push_back(first);

			while(currentToken().type() == CppLang::COMMA){
				incIndex();
				P_ADD_NODE(new ParameterCompiler())
			}
		}else{
			delete first;
		}

		P_EXPECT_TOKEN(CppLang::CLOSE_PAREN)
	}
	P_END
}

FunctionSignature FunctionSignatureCompiler::getSignature(){
	assert(children.size() > 0, "No function signature");

	Type returnType = children[0]->getType();
	if (returnType.isArray()) {
		printWarning("function returns pointer", getIndex());
		returnType.convertArrayToPointer();
	}

	dout("funsig return type = " << returnType.toString());
	dout("funsig name = " << identifier.value());
	FunctionSignature sig(identifier.value(), returnType);

	for(unsigned int i = 1; i < children.size(); i++){
		ParameterCompiler* param
			= static_cast<ParameterCompiler*>(children[i]);
		dout("param name = " << param->getName());
		dout("param type = " << param->getType().toString());
		sig.addParameter(param->getType(), param->getName());
	}

	dout("sig before return = " << sig.toString());

	return sig;
}