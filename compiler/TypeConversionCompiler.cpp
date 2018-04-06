#include "TypeConversionCompiler.hpp"

bool TypeConversionCompiler::convert(const Type& from, const Type& to){
	if (!typeManager.isPrimitive(from) || !typeManager.isPrimitive(to)){
		return false;
	}

	unsigned int fromSize = typeManager.sizeOf(from);
	if (fromSize == 0){
		return false;
	}
	unsigned int toSize = typeManager.sizeOf(to);
	
	writeComment("Converting " + from.toString() + " to " + to.toString());

	bool ok = true;
	if (to == Type("bool") && from != Type("bool")){
		ok = castToBool(from);
	}else{
		if (fromSize < toSize){
			ok = increaseSize(fromSize, toSize);
		}else{
			ok = decreaseSize(fromSize, toSize);
		}
	}
	writeComment("End type conversion");
	return ok;
}

bool TypeConversionCompiler::castToBool(Type from){
	unsigned int fromSize = typeManager.sizeOf(from);
	if (fromSize == 0){
		return false;
	}
	string end = newLabel();
	string falseLabel = newLabel();
	switch(fromSize){
		case 1:
			//test if positive
			writeAssembly("pushimm 0");
			writeAssembly("sub");
			writeAssembly("popinh");
			break;
		case 2:
			//test if positive
			writeAssembly("pushimm16 0");
			writeAssembly("jsr SUB16");
			writeAssembly("jsr TEST16");
			writeAssembly("popext PSW");
			writeAssembly("popinh16");
			break;
		default:
			return false;
	}
	writeAssembly("jnn " + falseLabel);
	writeAssembly("pushimm 1");
	writeAssembly("jump " + end);
	writeAssembly(falseLabel + ": pushimm 0");
	writeAssembly(end + ":");
	return true;
}

bool TypeConversionCompiler::increaseSize(unsigned int fromSize, unsigned int toSize){
	unsigned int diff = toSize - fromSize;
	if (fromSize == 0 || toSize < fromSize){
		return false;
	}else if (diff == 0){
		return true;
	}
	//maintain sign
	writeAssembly("test");
	string posLabel = newLabel();
	string endLabel = newLabel();
	writeAssembly("jnn " + posLabel);
	for(unsigned int i = 0; i < diff; i++){
		writeAssembly("pushimm 0xff");
	}
	writeAssembly("jump " + endLabel);
	writeAssembly(posLabel + ":");
	for(unsigned int i = 0; i < diff; i++){
		writeAssembly("pushimm 0");
	}
	writeAssembly(endLabel + ":");
	return true;
}

bool TypeConversionCompiler::decreaseSize(unsigned int fromSize, unsigned int toSize){
	if (toSize > fromSize){
		return false;
	}
	for(unsigned int i = toSize; i < fromSize; i++){
		writeAssembly("popinh");
	}
	return true;
}