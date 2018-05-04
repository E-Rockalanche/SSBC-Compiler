#include "IntegerCompiler.hpp"
#include <cctype>
using namespace std;

IntegerCompiler::~IntegerCompiler(){}

bool IntegerCompiler::parse(){
	Token token = currentToken();
	string str = token.value();
	value = 0;
	bool isLong = false;
	switch(token.type()){
		case CppLang::HEXADECIMAL:
			str = str.erase(0, 2);
			if (str == "") str = "0";
			isLong = str.size() > 2;
			value = stoi(str, NULL, 16);
			break;

		case CppLang::DECIMAL:
			if (toupper(str.back()) == 'L'){
				isLong = true;
				str.pop_back();
			}
			value = stoi(str);
			if ((value > SSBC_INT_MAX) || (value < SSBC_INT_MIN)){
				isLong = true;
			}
			break;

		case CppLang::OCTAL:
			value = stoi(str, NULL, 8);
			isLong = str.size() > 3;
			break;

		case CppLang::BINARY:
			str = str.erase(0, 2);
			if (str == "") str = "0";
			isLong = str.size() > 8;
			value = stoi(str, NULL, 2);
			break;
		default:
			return false;
	}

	if (isLong){
		type = Type("long", true);
	}else{
		type = Type("int", true);
	}
	
	incIndex();
	return true;
}

bool IntegerCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(type.isDefined(), "integer type is not defined");

	if (typeManager.sizeOf(type) == 1){
		writeAssembly("pushimm " + to_string(value));
	}else{
		writeAssembly("pushimm16 " + to_string(value));
	}
	return true;
}

int IntegerCompiler::getValue(){
	return value;
}