#include "ProgramCompiler.hpp"
#include "FunctionDefCompiler.hpp"

ProgramCompiler::~ProgramCompiler(){}

bool ProgramCompiler::parse(){
	#if(DEBUG)
		depth = 0;
	#endif
		
	P_BEGIN
	P_LOOP_NODE(new FunctionDefCompiler())
	if (index < tokens.size()){
		printError("Unparsed tokens");
		P_FAIL
	}
	P_END
}

bool ProgramCompiler::compile(){
	dout("Compiling in " << __FILE__);

	assert(children.size() > 0, "No statements");
	bool ok = true;
	for(unsigned int i = 0; i < children.size(); i++){
		if (!children[i]->compile()){
			ok = false;
		}
	}
	return ok;
}