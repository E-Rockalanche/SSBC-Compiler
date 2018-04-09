#include "UnaryExpCompiler.hpp"
#include "BitwiseNotCompiler.hpp"
#include "BooleanNotCompiler.hpp"
#include "DereferenceCompiler.hpp"
#include "ArrayAccessorCompiler.hpp"
#include "EnclosedExpCompiler.hpp"
#include "FunctionCallCompiler.hpp"
#include "VariableExpCompiler.hpp"
#include "LiteralCompiler.hpp"
#include "ReferenceExpCompiler.hpp"

UnaryExpCompiler::~UnaryExpCompiler(){}

bool UnaryExpCompiler::parse(){
	P_BEGIN
	P_TRY_NODE(new BitwiseNotCompiler())
	P_TRY_NODE(new ReferenceExpCompiler())
	P_TRY_NODE(new BooleanNotCompiler())
	P_TRY_NODE(new DereferenceCompiler())
	/*
	P_TRY_NODE(new IncrementCompiler())
	P_TRY_NODE(new DecrementCompiler())
	P_TRY_NODE(new PostIncrementCompiler())
	P_TRY_NODE(new PostDecrementCompiler())
	*/
	P_TRY_NODE(new ArrayAccessorCompiler())
	P_TRY_NODE(new EnclosedExpCompiler())
	P_TRY_NODE(new FunctionCallCompiler())
	P_TRY_NODE(new VariableExpCompiler())
	P_TRY_NODE(new LiteralCompiler())
	P_FAIL
}

bool UnaryExpCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No unary expression");
	return children.back()->compile();
}

Type UnaryExpCompiler::getType(){
	assert(children.size() > 0, "No unary expression");
	return children.back()->getType();
}