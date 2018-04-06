#include "MultiplicitiveExpCompiler.hpp"
#include "UnaryExpCompiler.hpp"
#include "TypeConversionCompiler.hpp"
#include <algorithm>
using namespace std;

MultiplicitiveExpCompiler::~MultiplicitiveExpCompiler(){}

bool MultiplicitiveExpCompiler::parse(){
	P_BEGIN
	//P_ADD_NODE(new MultiplicitiveExpCompiler())
	P_ADD_NODE(new UnaryExpCompiler())
	switch(currentToken().type()){
		case CppLang::ASTERISK:
		case CppLang::DIV:
		case CppLang::MOD:
			token = currentToken();
			incIndex();
			P_ADD_NODE(new MultiplicitiveExpCompiler())
			break;
		default:
			break;
	}
	P_END
}

bool MultiplicitiveExpCompiler::compile(){
	assert(children.size() > 0, "No multiplicitve expression");

	if (children.size() == 1){
		return children.back()->compile();
	}else{
		dout("Compiling in " << __FILE__);
		
		ASSERT_TYPES

		writeComment(token.value());

		Type t1 = children[0]->getType();
		Type t2 = children[1]->getType();
		type = getType();

		dout("Multiplicitive expression type = " << type.toString());

		int maxSize = typeManager.sizeOf(type);
		
		if (!children[1]->compile()) return false;
		TypeConversionCompiler::convert(t2, type);

		if (!children[0]->compile()) return false;
		TypeConversionCompiler::convert(t1, type);

		switch(token.type()){
			case CppLang::ASTERISK:
				if (maxSize == 1){
					writeAssembly("jsr MULT");
				}else{
					writeAssembly("jsr MULT16");
				}
				break;
			case CppLang::DIV:
				printError("integer division not implemented yet",
					children[1]->getIndex()-1);
				break;
			case CppLang::MOD:
				printError("modulo not implemented yet",
					children[1]->getIndex()-1);
				break;
			default:
				return false;
		}
		writeComment("End " + token.value());
	}

	return true;
}

Type MultiplicitiveExpCompiler::getType(){
	assert(children.size() > 0, "No multiplicitive expression");
	if (!type.isDefined()){
		if (children.size() == 2){
			Type t1 = children[0]->getType();
			Type t2 = children[1]->getType();
			if (t1.isDefined() && t2.isDefined()){
				int size = max(typeManager.sizeOf(t1), typeManager.sizeOf(t2));
				if (size == 1){
					type = Type("int");
				}else if (size == 2){
					type = Type("long");
				}else{
					printError("Cannot perform addition on types "
						+ t1.toString() + " and " + t2.toString());
				}
			}
		}else{
			type = children.back()->getType();
		}
	}
	return type;
}