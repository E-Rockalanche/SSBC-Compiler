#include "TypeManager.hpp"
#include "Debug.hpp"

unsigned int TypeManager::sizeOf(Type type) const{
	dout("TypeManager::sizeOf(" << type.toString() << ")");

	unsigned int size = 0;
	if (type.isArray()){
		return type.getArraySize() * sizeOf(type.removePointer());
	}else if (type.isPointer()){
		size = SSBC_PTR_SIZE;
	}else{
		string typeName = type.getBaseType();
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
			//check size of struct/class/union
			string msg = "Type " + typeName + " is not defined";
			throw runtime_error(msg);
		}
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