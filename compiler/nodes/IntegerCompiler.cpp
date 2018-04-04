#include "IntegerCompiler.hpp"

IntegerCompiler::~IntegerCompiler(){}

bool IntegerCompiler::parse(){
	Token token = currentToken();
	string str = token.value();
	value = 0;
	switch(token.type()){
		case CppLang::HEXADECIMAL:
			str = str.erase(0, 2);
			if (str == "") str = "0";
			value = stoi(str, NULL, 16);
			break;
		case CppLang::DECIMAL:
			value = stoi(str);
			break;
		case CppLang::OCTAL:
			value = stoi(str, NULL, 8);
			break;
		case CppLang::BINARY:
			str = str.erase(0, 2);
			if (str == "") str = "0";
			value = stoi(str, NULL, 2);
			break;
		default:
			return false;
	}
	
	if ((value <= 127) && (value >= -128)){
		type = Type("int", true);
	}else{
		type = Type("long", true);
	}
	incIndex();
	return true;
}

bool IntegerCompiler::compile(){
	dout("Compiling in " << __FILE__);

	if ((value < 256) && (value >= -128)){
		writeAssembly("pushimm " + to_string(value));
	}else{
		writeAssembly("pushimm16 " + to_string(value));
	}
	return true;
}