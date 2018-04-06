#include "ForLoopCompiler.hpp"
#include "StatementCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

ForLoopCompiler::~ForLoopCompiler(){}

bool ForLoopCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::FOR)
	P_EXPECT_TOKEN(CppLang::OPEN_PAREN)
	P_ADD_NODE(new StatementCompiler())
	P_EXPECT_TOKEN(CppLang::SEMICOLON)
	P_ADD_NODE(new ExpressionCompiler())
	P_EXPECT_TOKEN(CppLang::SEMICOLON)
	P_ADD_NODE(new StatementCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_PAREN)
	P_ADD_NODE(new StatementCompiler())
	P_END
}

bool ForLoopCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() == 4, "No while statement");

	//comppile initial statement
	children[0]->compile();

	string loopLabel = newLabel();
	string bodyLabel = newLabel();
	string endLabel = newLabel();

	writeAssembly(loopLabel + ":");

	//compile loop expression
	children[1]->compile();
	Type type = children[0]->getType();
	TypeConversionCompiler::convert(type, Type("bool"));

	writeAssembly("test popinh");
	writeAssembly("jnz " + bodyLabel);
	writeAssembly("jump " + endLabel);
	writeAssembly(bodyLabel + ":");

	//compile body
	children[3]->compile();

	//compile increment statement
	children[2]->compile();

	writeAssembly("jump " + loopLabel);

	writeAssembly(endLabel + ":");
	return true;
}