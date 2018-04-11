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

	dout("funsig return type = " << children[0]->getType().toString());
	dout("funsig name = " << identifier.value());
	FunctionSignature sig(identifier.value(), children[0]->getType());

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