#include "ParameterCompiler.hpp"
#include "TypeCompiler.hpp"
#include <stdexcept>
using namespace std;

ParameterCompiler::~ParameterCompiler(){}

bool ParameterCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new TypeCompiler())
	if (currentToken().type() == CppLang::IDENTIFIER){
		identifier = currentToken();
		incIndex();
		P_END
	}
	P_FAIL
}

Type ParameterCompiler::getType(){
	assert(children.size() > 0, "no parameter");
	return children.back()->getType();
}

string ParameterCompiler::getName(){
	assert(children.size() > 0, "no parameter");
	return identifier.value();
}