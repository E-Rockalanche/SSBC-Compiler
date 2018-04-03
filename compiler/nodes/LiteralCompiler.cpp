#include "LiteralCompiler.hpp"
#include "CharacterCompiler.hpp"
#include "StringCompiler.hpp"
#include "IntegerCompiler.hpp"

LiteralCompiler::~LiteralCompiler(){}

bool LiteralCompiler::parse(){
	P_BEGIN
	P_TRY_NODE(new CharacterCompiler())
	P_TRY_NODE(new StringCompiler())
	P_TRY_NODE(new IntegerCompiler())
	P_FAIL
}

bool LiteralCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No literal");
	return children.back()->compile();
}

Type LiteralCompiler::getType(){
	assert(children.size() > 0, "No literal");
	return children.back()->getType();
}