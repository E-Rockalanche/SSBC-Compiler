#include "ArgumentsCompiler.hpp"
#include "ExpressionCompiler.hpp"

ArgumentsCompiler::~ArgumentsCompiler(){}

bool ArgumentsCompiler::parse(){
	P_BEGIN;
	P_EXPECT_TOKEN(CppLang::OPEN_PAREN);
	CompilerNode* first = new ExpressionCompiler();
	if (first->parse()){
		children.push_back(first);
		while(currentToken().type() == CppLang::COMMA){
			incIndex();
			P_ADD_NODE(new ExpressionCompiler())
		}
	}else{
		delete first;
	}
	P_EXPECT_TOKEN(CppLang::CLOSE_PAREN);
	P_END;
}

bool ArgumentsCompiler::compile(){
	dout("Compiling in " << __FILE__);

	writeComment("Arguments");
	for(unsigned int i = 0; i < children.size(); i++){
		if (!children[i]->compile()){
			return false;
		}
	}
	writeComment("End arguments");
	return true;
}

bool ArgumentsCompiler::addParametersToSignature(FunctionSignature& function){
	for(unsigned int i = 0; i < children.size(); i++){
		Type t = children[i]->getType();
		if (!t.isDefined()){
			return false;
		}
		function.addParameter(t);
	}
	return true;
}

Type ArgumentsCompiler::getType(){
	throw runtime_error("Cannot call getType() on ArgumentCompiler");
}