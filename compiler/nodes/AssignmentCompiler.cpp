#include "AssignmentCompiler.hpp"
#include "AssignmentExpCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

AssignmentCompiler::~AssignmentCompiler(){}

bool AssignmentCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new AssignmentExpCompiler())
	P_EXPECT_TOKEN(CppLang::ASSIGN)
	P_ADD_NODE(new ExpressionCompiler())
	P_END
}

bool AssignmentCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() == 2, "No assignment");
	writeComment("Assignment");

	Type to = children[0]->getType();
	dout("left type = " << to.toString());

	Type from = children[1]->getType();
	dout("right type = " << from.toString());

	if (!children[1]->compile()) return false;
	TypeConversionCompiler::convert(from, to);

	if (!children[0]->compile()) return false;

	writeComment("End Assignment");
	return true;
}

Type AssignmentCompiler::getType(){
	throw runtime_error("Cannot get type of assignment");
}