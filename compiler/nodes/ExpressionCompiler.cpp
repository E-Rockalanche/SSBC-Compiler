#include "ExpressionCompiler.hpp"
#include "BooleanExpCompiler.hpp"

ExpressionCompiler::~ExpressionCompiler(){}

bool ExpressionCompiler::parse(){
	P_BEGIN
	P_TRY_NODE(new BooleanExpCompiler())
	P_FAIL
}

bool ExpressionCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No expression");
	return children.back()->compile();
}

Type ExpressionCompiler::getType(){
	assert(children.size() > 0, "No expression");
	return children.back()->getType();
}