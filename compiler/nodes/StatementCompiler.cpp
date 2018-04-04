#include "StatementCompiler.hpp"
#include "AssignmentCompiler.hpp"
#include "VariableDefCompiler.hpp"
#include "CompoundStatementCompiler.hpp"

StatementCompiler::~StatementCompiler(){}

bool StatementCompiler::parse(){
	P_BEGIN
	P_TRY_NODE(new CompoundStatementCompiler())
	P_TRY_NODE(new AssignmentCompiler())
	P_TRY_NODE(new VariableDefCompiler())
	P_FAIL
}

bool StatementCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No assignment");
	return children.back()->compile();
}