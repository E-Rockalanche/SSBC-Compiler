#include "TypeConversionCompiler.hpp"

bool TypeConversionCompiler::convert(const Type& from, const Type& to,
		unsigned int tokenIndex){
	if (convert(from, to)){
		return true;
	}else{
		printError("Cannot convert type " + from.toString() + " to "
			+ to.toString(), tokenIndex);
		return false;
	}
}

bool TypeConversionCompiler::convert(const Type& from, const Type& to){

	if (!from.isDefined() || !to.isDefined()){
		return false;
	}

	assert(!to.isReference() && !from.isReference(),
		"reference conversions not implemented yet");

	dout("converting " << from.toString() << " to " << to.toString());

	assert(typeManager.isPrimitive(from) && typeManager.isPrimitive(to),
		"non-primitives not supported yet");

	unsigned int fromSize = typeManager.sizeOf(from);
	if (fromSize == 0){
		return false;
	}

	if (to == from){
		return true;
	}
	
	writeComment("Converting " + from.toString() + " to " + to.toString());

	bool ok = false;
	if (to == Type("bool")){
		ok = toBool(from);
	}else if (to == Type("int")){
		ok = toInt(from);
	}else if (to == Type("long")){
		ok = toLong(from);
	}else if (to == Type("char")){
		ok = toChar(from);
	}else if (to == Type("void")){
		ok = toVoid(from);
	}else if (to.isArray()){
		ok = toArray(from, to);
	}else if (to.isPointer()){
		ok = toPointer(from, to);
	}else{
		assert(false, "unchecked case for type conversion: " + from.toString()
			+ " to " + to.toString());
	}

	writeComment("End type conversion");

	return ok;
}

bool TypeConversionCompiler::toBool(Type from){
	unsigned int fromSize = typeManager.sizeOf(from);
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
			assert(false, "Cannot convert type size greater than 2 to bool");
			return false;
	}
	writeAssembly("jnn " + falseLabel);
	writeAssembly("pushimm 1");
	writeAssembly("jump " + end);
	writeAssembly(falseLabel + ": pushimm 0");
	writeAssembly(end + ":");
	return true;
}

bool TypeConversionCompiler::toInt(Type from){
	return adjustSize(typeManager.sizeOf(from), SSBC_INT_SIZE);
}

bool TypeConversionCompiler::toLong(Type from){
	return adjustSize(typeManager.sizeOf(from), SSBC_LONG_SIZE);
}

bool TypeConversionCompiler::toChar(Type from){
	return adjustSize(typeManager.sizeOf(from), SSBC_CHAR_SIZE);
}

bool TypeConversionCompiler::toPointer(Type from, Type to){
	bool ok = false;
	if (!from.isPointer() && typeManager.isPrimitive(from)){
		ok =  adjustSize(typeManager.sizeOf(from), typeManager.sizeOf(to));
	}else if (from.isArray() || from.isPointer()){
		from.removePointer();
		to.removePointer();
		if (from.numPointers() == to.numPointers()){
			ok = (typeManager.sizeOf(from.getBaseType())
				== typeManager.sizeOf(to.getBaseType()));
		}
	}
	return ok;
}

bool TypeConversionCompiler::toReference(Type from, Type to){
	assert(false, "references not implemented yet");
	return false;
}

bool TypeConversionCompiler::toArray(Type from, Type to){
	return (to.isArray()
		&& to.getArraySize() == from.getArraySize()
		&& toPointer(from, to));
}

bool TypeConversionCompiler::toVoid(Type from){
	return (typeManager.sizeOf(from) == 0);
}

bool TypeConversionCompiler::adjustSize(unsigned int fromSize,
		unsigned int toSize){
	if (toSize > fromSize){
		return increaseSize(fromSize, toSize);
	}else if (fromSize > toSize){
		return decreaseSize(fromSize, toSize);
	}
	return true;
}

bool TypeConversionCompiler::increaseSize(unsigned int fromSize,
		unsigned int toSize){
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

bool TypeConversionCompiler::decreaseSize(unsigned int fromSize,
		unsigned int toSize){
	if (toSize > fromSize){
		return false;
	}
	for(unsigned int i = toSize; i < fromSize; i++){
		writeAssembly("popinh");
	}
	return true;
}