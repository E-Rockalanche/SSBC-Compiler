#include "LiteralCompiler.hpp"
#include "CharacterCompiler.hpp"
#include "StringCompiler.hpp"
#include "IntegerCompiler.hpp"
#include "ArrayLiteralCompiler.hpp"

LiteralCompiler::~LiteralCompiler(){}

bool LiteralCompiler::parse(){
	P_BEGIN
	P_TRY_NODE(new ArrayLiteralCompiler())
	P_TRY_NODE(new CharacterCompiler())
	P_TRY_NODE(new StringCompiler())
	P_TRY_NODE(new IntegerCompiler())
	P_FAIL
}

bool LiteralCompiler::compile(){
	dout("Compiling in " << __FILE__);

	writeComment("Literal");
	assert(children.size() > 0, "No literal");
	return children.back()->compile();
	writeComment("End literal");
}

Type LiteralCompiler::getType(){
	assert(children.size() > 0, "No literal");
	return children.back()->getType();
}

int LiteralCompiler::getValue(){
	return children.back()->getValue();
}