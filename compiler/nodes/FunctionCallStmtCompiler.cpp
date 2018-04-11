#include "FunctionCallStmtCompiler.hpp"
#include "FunctionCallCompiler.hpp"

FunctionCallStmtCompiler::~FunctionCallStmtCompiler(){}

bool FunctionCallStmtCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new FunctionCallCompiler())
	P_END
}

bool FunctionCallStmtCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(children.size() > 0, "no function call statement");

	children.back()->compile();
	unsigned int typeSize = typeManager.sizeOf(children.back()->getType());
	for(unsigned int i = 0; i < typeSize; i++){
		writeAssembly("popinh");
	}

	return true;
}