#include "ReturnCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TypeConversionCompiler.hpp"

ReturnCompiler::~ReturnCompiler(){}

bool ReturnCompiler::parse(){
	P_BEGIN

	returns = true;

	P_EXPECT_TOKEN(CppLang::RETURN)
	P_OPTIONAL_NODE(new ExpressionCompiler())
	P_END
}

bool ReturnCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(!scopeTable.inGlobalScope(), "return in global scope");

	bool hasExpression = (children.size() > 0);
	bool returnsValue = (typeManager.sizeOf(functionReturnType) > 0);
	if (hasExpression != returnsValue){
		printError("Returning " + getType().toString() + " in function returning "
			+ functionReturnType.toString());
		return false;
	}

	if(children.size() > 0){
		writeComment("Calculating return value");
		children.back()->compile();
		Type from = children.back()->getType();
		TypeConversionCompiler::convert(from, functionReturnType);
	}

	writeComment("Return");
	writeAssembly("jump " + functionReturnLabel);

	return true;
}

Type ReturnCompiler::getType(){
	if (children.size() == 0){
		return Type("void");
	}else{
		return children.back()->getType();
	}
}