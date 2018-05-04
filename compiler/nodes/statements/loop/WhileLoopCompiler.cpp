#include "WhileLoopCompiler.hpp"
#include "StatementCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

WhileLoopCompiler::~WhileLoopCompiler(){}

bool WhileLoopCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::WHILE)
	P_EXPECT_TOKEN(CppLang::OPEN_PAREN)
	P_ADD_NODE(new ExpressionCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_PAREN)
	P_ADD_NODE(new StatementCompiler())
	P_END
}

bool WhileLoopCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() == 2, "No while statement");

	writeComment("While Loop");

	string loopLabel = newLabel();
	string bodyLabel = newLabel();
	string endLabel = newLabel();

	scopeTable.pushScope();

	writeAssembly(loopLabel + ":");

	children[0]->compile();
	Type type = children[0]->getType();
	TypeConversionCompiler::convert(type, Type("bool"));

	writeAssembly("test popinh");
	writeAssembly("jnz " + bodyLabel);
	writeAssembly("jump " + endLabel);
	writeAssembly(bodyLabel + ":");

	//body
	breakManager.pushLoop(endLabel, loopLabel);
	children[1]->compile();
	breakManager.popScope();

	writeAssembly("jump " + loopLabel);

	writeAssembly(endLabel + ":");

	scopeTable.popScope();

	return true;
}