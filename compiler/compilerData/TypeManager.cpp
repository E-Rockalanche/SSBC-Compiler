#include "TypeManager.hpp"
#include "Debug.hpp"

unsigned int TypeManager::sizeOf(Type type) const{
	dout("TypeManager::sizeOf(" << type.toString() << ")");

	unsigned int size = 0;
	if (type.isArray()){
		size = type.getArraySize() * sizeOf(type.removePointer());
	}else if (type.isPointer() || type.isReference()){
		size = SSBC_PTR_SIZE;
	}else{
		size = sizeOf(type.getBaseType());
	}
	return size;
}

unsigned int TypeManager::sizeOf(string typeName) const {
	unsigned int size;
	if (typeName == "void"){
		size = SSBC_VOID_SIZE;
	}else if (typeName == "int"){
		size = SSBC_INT_SIZE;
	}else if (typeName == "char"){
		size = SSBC_CHAR_SIZE;
	}else if (typeName == "bool"){
		size = SSBC_BOOL_SIZE;
	}else if (typeName == "long"){
		size = SSBC_LONG_SIZE;
	}else{
		// TODO check size of struct/class/union
		throw runtime_error("type " + typeName + " is not defined");
	}
	return size;
}

bool TypeManager::isPrimitive(const Type& type) const{
	string typeName = type.getBaseType();
	return (typeName == "void") || (typeName == "int")
		|| (typeName == "char") || (typeName == "bool")
		|| (typeName == "long");
}

bool TypeManager::typeExists(const string& typeName) const{
	return (typeName == "void") || (typeName == "int")
		|| (typeName == "char") || (typeName == "bool")
		|| (typeName == "long");
}

void TypeManager::clear(){
	//remove class and struct definitions
}