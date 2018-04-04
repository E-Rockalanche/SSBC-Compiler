#include "EqualityExpCompiler.hpp"
#include "AdditiveExpCompiler.hpp"

EqualityExpCompiler::~EqualityExpCompiler(){}

bool EqualityExpCompiler::parse(){
	P_BEGIN
	//P_ADD_NODE(new MultiplicitiveExpCompiler())
	P_ADD_NODE(new AdditiveExpCompiler())
	switch(currentToken().type()){
		case CppLang::EQUALS:
		case CppLang::NOT_EQUALS:
			token = currentToken();
			incIndex();
			P_ADD_NODE(new EqualityExpCompiler())
			break;
		default:
			break;
	}
	P_END
}

bool EqualityExpCompiler::compile(){

	assert(children.size() > 0, "No additive expression");

	if (children.size() == 1){
		return children.back()->compile();
	}else{
		dout("Compiling in " << __FILE__);

		ASSERT_TYPES

		writeComment(token.value());
		Type t1 = children[0]->getType();
		Type t2 = children[1]->getType();
		unsigned int maxSize = max(typeManager.sizeOf(t1), typeManager.sizeOf(t2));
		
		if (!children[0]->compile()) return false;
		if (typeManager.sizeOf(t1) < maxSize){
			compileTypeConversion(t1, t2);
		}

		if (!children[1]->compile()) return false;
		if (typeManager.sizeOf(t2) < maxSize){
			compileTypeConversion(t2, t1);
		}

		if (maxSize == 1){
			writeAssembly("sub");
			writeAssembly("popinh");
		}else{
			writeAssembly("jsr SUB16");
			writeAssembly("jsr TEST16");
			writeAssembly("popext PSW");
			writeAssembly("popinh16");
		}

		string notEquals = newLabel();
		string end = newLabel();
		writeAssembly("jnz " + notEquals);

		switch(token.type()){
			case CppLang::EQUALS:
				writeAssembly("pushimm 1");
				writeAssembly("jump " + end);
				writeAssembly(notEquals + ": pushimm 0");
				break;
			case CppLang::NOT_EQUALS:
				writeAssembly("pushimm 0");
				writeAssembly("jump " + end);
				writeAssembly(notEquals + ": pushimm 1");
				break;
			default:
				return false;
		}
		writeAssembly(end + ":");
		writeComment("End " + token.value());
	}

	return true;
}

Type EqualityExpCompiler::getType(){
	assert(children.size() > 0, "No additive expression");
	if (children.size() == 2){
		return Type("bool");
	}else{
		return children.back()->getType();
	}
}