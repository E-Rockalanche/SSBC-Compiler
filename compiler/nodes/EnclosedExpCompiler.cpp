#include "EnclosedExpCompiler.hpp"
#include "ExpressionCompiler.hpp"

EnclosedExpCompiler::~EnclosedExpCompiler(){}

bool EnclosedExpCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::OPEN_PAREN)
	P_ADD_NODE(new ExpressionCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_PAREN)
	P_END
}

bool EnclosedExpCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No enclosed expression");
	return children.back()->compile();
}

Type EnclosedExpCompiler::getType(){
	assert(children.size() > 0, "No enclosed expression");
	return children.back()->getType();
}