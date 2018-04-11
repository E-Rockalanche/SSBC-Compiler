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
	for(unsigned int i = 0; i < children.size(); i++){
		if (endsSequence || returns){
			printWarning("Unexecuted statements",
				children[i]->getIndex());
			break;
		}else{
			numErrors += !children[i]->compile();
			if (children[i]->returnsFromFunction()){
				returns = true;
			}else if (children[i]->endsStatementSequence()){
				endsSequence = true;
			}
		}
	}
	return (numErrors == 0);
}