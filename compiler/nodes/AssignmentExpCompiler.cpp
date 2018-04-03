#include "AssignmentExpCompiler.hpp"
#include "ArrayAssignmentCompiler.hpp"
#include "VariableAssignmentCompiler.hpp"

AssignmentExpCompiler::~AssignmentExpCompiler(){}

bool AssignmentExpCompiler::parse(){
	P_BEGIN
	P_TRY_NODE(new ArrayAssignmentCompiler())
	P_TRY_NODE(new VariableAssignmentCompiler())
	P_FAIL
}

bool AssignmentExpCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No assignment expression");
	return children.back()->compile();
}

Type AssignmentExpCompiler::getType(){
	assert(children.size() > 0, "No assignment expression type");
	return children.back()->getType();
}