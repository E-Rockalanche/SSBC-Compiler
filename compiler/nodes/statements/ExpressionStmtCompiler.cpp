#include "ExpressionStmtCompiler.hpp"
#include "expresion/ExpressionCompiler.hpp"

ExpressionStmtCompiler::~ExpressionStmtCompiler(){}

bool ExpressionStmtCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new ExpressionCompiler())
	P_END
}

bool ExpressionStmtCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(children.size() > 0, "no function call statement");

	children.back()->compile();
	unsigned int typeSize = typeManager.sizeOf(children.back()->getType());
	for(unsigned int i = 0; i < typeSize; i++){
		writeAssembly("popinh");
	}

	return true;
}