#include "BooleanExpCompiler.hpp"
#include "RelationalExpCompiler.hpp"

BooleanExpCompiler::~BooleanExpCompiler(){}

bool BooleanExpCompiler::parse(){
	P_BEGIN
	//P_ADD_NODE(new MultiplicitiveExpCompiler())
	P_ADD_NODE(new RelationalExpCompiler())
	switch(currentToken().type()){
		case CppLang::AND:
		case CppLang::OR:
			token = currentToken();
			incIndex();
			P_ADD_NODE(new BooleanExpCompiler())
			break;
		default:
			break;
	}
	P_END
}

bool BooleanExpCompiler::compile(){
	assert(children.size() > 0, "No boolean expression");
	
	if (children.size() == 1){
		return children.back()->compile();
	}else{
		dout("Compiling in " << __FILE__);

		ASSERT_TYPES

		writeComment(token.value());
		Type t1 = children[0]->getType();
		Type t2 = children[1]->getType();
	
		if (!children[0]->compile()) return false;
		compileTypeConversion(t1, Type("bool"));
		writeAssembly("test");

		string end = newLabel();

		if (token.type() == CppLang::OR){
			writeAssembly("jnz " + end);
			writeAssembly("popinh");

			if (!children[1]->compile()) return false;
			compileTypeConversion(t2, Type("bool"));
			writeAssembly("test");

			writeAssembly("jnz " + end);
			//another 0 is left on stack
			writeAssembly("jump " + end);
		}else if (token.type() == CppLang::AND){
			string test2 = newLabel();
			writeAssembly("jnz " + test2);
			//0 left on stack
			writeAssembly("jump " + end);
			writeAssembly(test2 + ":");
			writeAssembly("popinh");

			if (!children[1]->compile()) return false;
			compileTypeConversion(t2, Type("bool"));
			writeAssembly("test");

			writeAssembly("jnz " + end);
			//0 left on stack
			writeAssembly("jump " + end);
		}
		writeAssembly(end + ":");
		//0 or 1 should be on top of stack
		writeComment("End " + token.value());
	}
	
	return true;
}

Type BooleanExpCompiler::getType(){
	assert(children.size() > 0, "No boolean expression");
	if (children.size() == 2){
		return Type("bool");
	}else{
		return children.back()->getType();
	}
}