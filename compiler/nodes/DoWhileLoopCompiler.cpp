#include "DoWhileLoopCompiler.hpp"
#include "StatementCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

DoWhileLoopCompiler::~DoWhileLoopCompiler(){}

bool DoWhileLoopCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::DO)
	P_ADD_NODE(new StatementCompiler())
	P_EXPECT_TOKEN(CppLang::WHILE)
	P_EXPECT_TOKEN(CppLang::OPEN_PAREN)
	P_ADD_NODE(new ExpressionCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_PAREN)
	P_END
}

bool DoWhileLoopCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(children.size() == 2, "No do while statement");

	//start loop
	string loopLabel = newLabel();
	writeAssembly(loopLabel + ":");

	//loop body
	children[0]->compile();

	//test expression
	children[1]->compile();
	Type type = children[1]->getType();
	TypeConversionCompiler::convert(type, Type("bool"));

	writeAssembly("test popinh");
	writeAssembly("jnz " + loopLabel);
	return true;
}