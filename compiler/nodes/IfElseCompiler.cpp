#include "IfElseCompiler.hpp"
#include "StatementCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

IfElseCompiler::~IfElseCompiler(){}

bool IfElseCompiler::parse(){
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

bool IfElseCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() >= 2, "No if statement");

	//compile expression
	children[0]->compile();
	Type type = children[0]->getType();
	TypeConversionCompiler::convert(type, Type("bool"));

	string trueLabel = newLabel();
	string falseLabel = newLabel();
	string endLabel = newLabel();

	writeAssembly("test popinh");
	writeAssembly("jnz " + trueLabel);
	writeAssembly("jump " + falseLabel);
	writeAssembly(trueLabel + ": ");

	//compile if body
	children[1]->compile();

	writeAssembly("jump " + endLabel);

	writeAssembly(falseLabel + ": ");

	if (children.size() == 3){
		//compile else body
		children[2]->compile();

		returns = (children[1]->returnsFromFunction()
			&& children[2]->returnsFromFunction());
		
		endsSequence = (children[1]->endsStatementSequence()
			&& children[2]->endsStatementSequence());
	}else{
		returns = false;
		endsSequence = false;
	}

	writeAssembly(endLabel + ": ");
	return true;
}