#include "ArrayLiteralCompiler.hpp"
#include "LiteralCompiler.hpp"
#include "TypeConversionCompiler.hpp"

ArrayLiteralCompiler::~ArrayLiteralCompiler(){}

bool ArrayLiteralCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::OPEN_BRACE)
	P_ADD_NODE(new LiteralCompiler())
	while(currentToken().type() == CppLang::COMMA){
		incIndex();
		P_ADD_NODE(new LiteralCompiler())
	}
	P_EXPECT_TOKEN(CppLang::CLOSE_BRACE)
	P_END
}

bool ArrayLiteralCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(children.size() > 0, "No array literal");

	elementType = children[0]->getType();

	writeComment("Array literal");
	for(int i = (int)children.size() - 1; i >= 0; i--){
		children[i]->compile();
		TypeConversionCompiler::convert(children[i]->getType(), elementType);
	}
	writeComment("End array literal");
	return true;
}

Type ArrayLiteralCompiler::getType(){
	assert(children.size() > 0, "No literal");
	assert(elementType.isDefined(),
		"element type of array literal is not defined");
	return elementType.makeArray(children.size(), true);
}

void ArrayLiteralCompiler::setElementType(Type type){
	assert(type.isDefined(), "cannot set element type to undefined");
	elementType = type;
}