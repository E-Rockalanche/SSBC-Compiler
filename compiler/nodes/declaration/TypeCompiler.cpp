#include "TypeCompiler.hpp"
#include "IntegerCompiler.hpp"

TypeCompiler::~TypeCompiler(){}

//parses and creates a Type object
bool TypeCompiler::parse(){
	P_BEGIN

	bool isConstant = false;
	bool isStatic = false;
	bool isArray = false;
	bool isReference = false;
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

		//array
		if (currentToken().type() == CppLang::OPEN_BRACKET) {
			incIndex();

			P_ADD_NODE(new IntegerCompiler())
			P_EXPECT_TOKEN(CppLang::CLOSE_BRACKET);

			type.makeArray(children[0]->getValue());
			isArray = true;
		}

		/*
		//uncomment to activate
		else if (currentToken().type() == CppLang::AMPERSAND) {
			type.makeReference();
			isReference = true;
		}
		*/
		P_END
	} else {
		P_FAIL
	}
}

bool TypeCompiler::compile(){
	throw runtime_error("Types cannot be compiled");
}