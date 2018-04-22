#include "GlobalStatementCompiler.hpp"
#include "FunctionDefCompiler.hpp"

GlobalStatementCompiler::~GlobalStatementCompiler(){}

bool GlobalStatementCompiler::parse(){
	P_BEGIN
	P_TRY_NODE(new FunctionDefCompiler())
	P_FAIL
}

bool GlobalStatementCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(children.size() > 0, "No global statement");
	
	return children.back()->compile();
}