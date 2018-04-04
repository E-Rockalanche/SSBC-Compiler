#include "TypeCompiler.hpp"

TypeCompiler::~TypeCompiler(){}

//parses and creates a Type object
bool TypeCompiler::parse(){
	P_BEGIN

	bool isConstant = false;
	bool isStatic = false;
	string name = "";
	bool continueLoop = true;
	do{
		switch(currentToken().type()){
			case CppLang::CONST:
				if (isConstant){
					printWarning("const already declared", index);
				}
				isConstant = true;
				break;
			case CppLang::STATIC:
				if (isStatic){
					printWarning("static already declared", index);
				}
				isStatic = true;
				break;
			case CppLang::IDENTIFIER:
				if (name == ""){
					name = currentToken().value();
				}else{
					continueLoop = false;
				}
				break;
			default:
				continueLoop = false;
				break;
		}
		if (continueLoop){
			incIndex();
		}
	}while(continueLoop);

	if (name != ""){
		type = Type(name, isConstant);
		while(currentToken().type() == CppLang::ASTERISK){
			isConstant = false;
			incIndex();
			if (currentToken().type() == CppLang::CONST){
				isConstant = true;
				incIndex();
			}
			type.addPointer(isConstant);
		}
		P_END
	}
	P_FAIL
}

bool TypeCompiler::compile(){
	throw runtime_error("Type cannot be compiled");
}