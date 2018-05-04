#include "ArrayDeclarationCompiler.hpp"
#include "IntegerCompiler.hpp"
#include <stdexcept>
using namespace std;

ArrayDeclarationCompiler::~ArrayDeclarationCompiler(){}

bool ArrayDeclarationCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::OPEN_BRACKET)
	P_ADD_NODE(new IntegerCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_BRACKET)
	P_END
}

bool ArrayDeclarationCompiler::compile(){
	throw runtime_error("Cannot compile array declaration");
	return false;
}

int ArrayDeclarationCompiler::getValue(){
	int value = children.back()->getValue();
	if (value <= 0){
		printError("Cannot declare array size less than 1", startTokenIndex+1);
		return 1;
	}else{
		return value;
	}
}