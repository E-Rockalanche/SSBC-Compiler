#include "CompoundStatementCompiler.hpp"
#include "StatementCompiler.hpp"

CompoundStatementCompiler::~CompoundStatementCompiler(){}

bool CompoundStatementCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::OPEN_BRACE)
	P_LOOP_NODE(new StatementCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_BRACE)
	P_END
}

bool CompoundStatementCompiler::compile(){
	dout("Compiling in " << __FILE__);

	scopeTable.pushScope();

	bool ok = true;
	for(unsigned int i = 0; i < children.size(); i++){
		if (!children[i]->compile()){
			ok = false;
		}
	}

	scopeTable.popScope();

	return ok;
}