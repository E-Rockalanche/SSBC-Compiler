#include "StatementCompiler.hpp"
#include "AssignmentCompiler.hpp"
#include "VariableDefCompiler.hpp"
#include "CompoundStatementCompiler.hpp"
#include "IfElseCompiler.hpp"
#include "WhileLoopCompiler.hpp"
#include "DoWhileLoopCompiler.hpp"
#include "ForLoopCompiler.hpp"
#include "ExitCompiler.hpp"
#include "SwitchCompiler.hpp"
#include "BreakCompiler.hpp"
#include "ContinueCompiler.hpp"

StatementCompiler::~StatementCompiler(){}

bool StatementCompiler::parse(){
	P_BEGIN
	P_TRY_NODE(new IfElseCompiler())
	P_TRY_NODE(new WhileLoopCompiler())
	P_TRY_NODE(new DoWhileLoopCompiler())
	P_TRY_NODE(new ForLoopCompiler())
	P_TRY_NODE(new ExitCompiler())
	P_TRY_NODE(new BreakCompiler())
	P_TRY_NODE(new ContinueCompiler())
	P_TRY_NODE(new SwitchCompiler())
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