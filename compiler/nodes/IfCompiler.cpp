#include "IfCompiler.hpp"
#include "StatementCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

IfCompiler::~IfCompiler(){}

bool IfCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::IF)
	P_EXPECT_TOKEN(CppLang::OPEN_PAREN)
	P_ADD_NODE(new ExpressionCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_PAREN)
	P_ADD_NODE(new StatementCompiler())
	if (currentToken().type() == CppLang::ELSE){
		incIndex();
		P_ADD_NODE(new StatementCompiler())
	}
	P_END
}

bool IfCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() >= 2, "No if statement");

	children[0]->compile();
	Type type = children[0]->getType();
	TypeConversionCompiler::convert(type, Type("bool"));

	string trueLabel = newLabel();
	string falseLabel = newLabel();
	string endLabel = newLabel();

	writeAssembly("test");
	writeAssembly("jnz " + trueLabel);
	writeAssembly("jump " + falseLabel);
	writeAssembly(trueLabel + ": ");

	children[1]->compile();

	writeAssembly("jump " + endLabel);

	writeAssembly(falseLabel + ": ");

	if (children.size() == 3){
		children[2]->compile();
	}

	writeAssembly(endLabel + ": ");
	return true;
}