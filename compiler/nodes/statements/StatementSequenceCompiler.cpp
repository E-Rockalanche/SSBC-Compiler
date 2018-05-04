#include "StatementSequenceCompiler.hpp"
#include "StatementCompiler.hpp"

StatementSequenceCompiler::~StatementSequenceCompiler(){}

bool StatementSequenceCompiler::parse(){
	P_BEGIN
	P_LOOP_NODE(new StatementCompiler())
	P_END
}

bool StatementSequenceCompiler::compile(){
	dout("Compiling in " << __FILE__);

	int numErrors = 0;
	bool stopSequence = false;
	for(unsigned int i = 0; i < children.size(); i++){
		if (stopSequence){
			printWarning("Unexecuted statements",
				children[i]->getIndex());
			break;
		}else{
			numErrors += !children[i]->compile();
			if (children[i]->returnsFromFunction()
				|| children[i]->endsStatementSequence()){
				stopSequence = true;
			}
		}
	}
	return (numErrors == 0);
}

bool StatementSequenceCompiler::endsStatementSequence() {
	for(unsigned int i = 0; i < children.size(); i++) {
		if (children->endsStatementSequence()) {
			return true;
		}
	}
	return false;
}

bool StatementSequenceCompiler::returnsFromFunction() {
	for(unsigned int i = 0; i < children.size(); i++) {
		if (children->returnsFromFunction()) {
			return true;
		}
	}
	return false;
}