#include "AdditiveExpCompiler.hpp"
#include "UnaryExpCompiler.hpp"
#include <algorithm>
using namespace std;

AdditiveExpCompiler::~AdditiveExpCompiler(){}

bool AdditiveExpCompiler::parse(){
	P_BEGIN
	//P_ADD_NODE(new MultiplicitiveExpCompiler())
	P_ADD_NODE(new UnaryExpCompiler())
	switch(currentToken().type()){
		case CppLang::ADD:
		case CppLang::SUB:
			token = currentToken();
			incIndex();
			P_ADD_NODE(new AdditiveExpCompiler())
			break;
		default:
			break;
	}
	P_END
}

bool AdditiveExpCompiler::compile(){

	assert(children.size() > 0, "No additive expression");

	if (children.size() == 1){
		return children.back()->compile();
	}else{
		dout("Compiling in " << __FILE__);
		
		ASSERT_TYPES

		writeComment(token.value());

		Type t1 = children[0]->getType();
		Type t2 = children[1]->getType();
		type = getType();

		dout("Additive expression type = " << type.toString());

		int maxSize = typeManager.sizeOf(type);
		
		if (!children[1]->compile()) return false;
		compileTypeConversion(t2, type);

		if (!children[0]->compile()) return false;
		compileTypeConversion(t1, type);

		switch(token.type()){
			case CppLang::ADD:
				if (maxSize == 1){
					writeAssembly("add");
				}else{
					writeAssembly("jsr ADD16");
				}
				break;
			case CppLang::SUB:
				if (maxSize == 1){
					writeAssembly("sub");
				}else{
					writeAssembly("jsr SUB16");
				}
				break;
			default:
				return false;
		}
		writeComment("End " + token.value());
	}

	return true;
}

Type AdditiveExpCompiler::getType(){
	assert(children.size() > 0, "No additive expression");
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