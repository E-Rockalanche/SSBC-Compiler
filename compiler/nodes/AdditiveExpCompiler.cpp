#include "AdditiveExpCompiler.hpp"
#include "UnaryExpCompiler.hpp"

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
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No additive expression");

	for(unsigned int i = 0; i < children.size(); i++){
		Type t = children[i]->getType();
		if (!t.isDefined()){
			printError("Expression type undefined", children[i]->getIndex());
			return false;
		}else if (t == Type("void")){
			printError("Expression returns void", children[i]->getIndex());
			return false;
		}
	}
	if (children.size() == 1){
		return children.back()->compile();
	}else{
		writeComment(token.value());
		type = getType();
		if (!type.isDefined()) return false;

		Type t1 = children[0]->getType();
		Type t2 = children[1]->getType();
		int maxSize = max(typeManager.sizeOf(t1), typeManager.sizeOf(t2));
		
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
			if (t1 == Type()){
				printError("Undefined type", children[0]->getIndex());
				type = Type();
			}
			if (t2 == Type()){
				printError("Undefined type", children[1]->getIndex());
				type = Type();
			}
			type = (typeManager.sizeOf(t1) > typeManager.sizeOf(t2)) ? t1 : t2;
		}else{
			type = children.back()->getType();
		}
	}
	return type;
}