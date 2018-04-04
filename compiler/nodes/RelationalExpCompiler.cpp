#include "RelationalExpCompiler.hpp"
#include "EqualityExpCompiler.hpp"

RelationalExpCompiler::~RelationalExpCompiler(){}

bool RelationalExpCompiler::parse(){
	P_BEGIN
	//P_ADD_NODE(new MultiplicitiveExpCompiler())
	P_ADD_NODE(new EqualityExpCompiler())
	switch(currentToken().type()){
		case CppLang::LESSER:
		case CppLang::GREATER:
		case CppLang::LESSER_EQUALS:
		case CppLang::GREATER_EQUALS:
			token = currentToken();
			incIndex();
			P_ADD_NODE(new RelationalExpCompiler())
			break;
		default:
			break;
	}
	P_END
}

bool RelationalExpCompiler::compile(){
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
		
		if ((token.type() == CppLang::GREATER)
			|| (token.type() == CppLang::LESSER_EQUALS)){
			//must compile first child first
			if (!children[0]->compile()) return false;
			if (typeManager.sizeOf(t1) < maxSize){
				compileTypeConversion(t1, t2);
			}
		}

		if (!children[1]->compile()) return false;
		if (typeManager.sizeOf(t2) < maxSize){
			compileTypeConversion(t2, t1);
		}

		if ((token.type() == CppLang::LESSER)
			|| (token.type() == CppLang::GREATER_EQUALS)){
			//must compile first child second
			if (!children[0]->compile()) return false;
			if (typeManager.sizeOf(t1) < maxSize){
				compileTypeConversion(t1, t2);
			}
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

		string positive = newLabel();
		string end = newLabel();
		writeAssembly("jnn " + positive);

		switch(token.type()){
			case CppLang::GREATER:
			case CppLang::LESSER:
				writeAssembly("pushimm 1");
				writeAssembly("jump " + end);
				writeAssembly(positive + ": pushimm 0");
				break;
			case CppLang::GREATER_EQUALS:
			case CppLang::LESSER_EQUALS:
				writeAssembly("pushimm 0");
				writeAssembly("jump " + end);
				writeAssembly(positive + ": pushimm 1");
				break;
			default:
				return false;
		}
		writeAssembly(end + ":");
		writeComment("End " + token.value());
	}

	return true;
}

Type RelationalExpCompiler::getType(){
	assert(children.size() > 0, "No additive expression");
	if (children.size() == 2){
		return Type("bool");
	}else{
		return children.back()->getType();
	}
}