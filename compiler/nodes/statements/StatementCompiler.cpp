#include "StatementCompiler.hpp"
#include "CompoundStatementCompiler.hpp"
#include "FunctionCallStmtCompiler.hpp"

#include "assignment/AssignmentCompiler.hpp"
#include "assignment/VariableDefCompiler.hpp"

#include "selection/IfElseCompiler.hpp"
#include "selection/SwitchCompiler.hpp"

#include "loop/WhileLoopCompiler.hpp"
#include "loop/DoWhileLoopCompiler.hpp"
#include "loop/ForLoopCompiler.hpp"

#include "jump/ExitCompiler.hpp"
#include "jump/BreakCompiler.hpp"
#include "jump/ContinueCompiler.hpp"
#include "jump/ReturnCompiler.hpp"


StatementCompiler::~StatementCompiler(){}

bool StatementCompiler::parse(){
	P_BEGIN
	P_TRY_NODE(new ReturnCompiler())
	P_TRY_NODE(new IfElseCompiler())
	P_TRY_NODE(new WhileLoopCompiler())
	P_TRY_NODE(new DoWhileLoopCompiler())
	P_TRY_NODE(new ForLoopCompiler())
	P_TRY_NODE(new ExitCompiler())
	P_TRY_NODE(new BreakCompiler())
	P_TRY_NODE(new ContinueCompiler())
	P_TRY_NODE(new SwitchCompiler())
	P_TRY_NODE(new CompoundStatementCompiler())
	P_TRY_NODE(new VariableDefCompiler())
	P_TRY_NODE(new AssignmentCompiler())
	P_TRY_NODE(new FunctionCallStmtCompiler())
	P_FAIL
}

bool StatementCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No assignment");
	return children.back()->compile();
}

bool StatementCompiler::endsStatementSequence() {
	return children.back()->endsStatementSequence();
}

bool StatementCompiler::returnsFromFunction() {
	return children.back()->returnsFromFunction();
}