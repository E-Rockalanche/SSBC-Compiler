#include "TypeManager.hpp"
#include "Debug.hpp"

unsigned int TypeManager::sizeOf(const Type& type) const{
	dout("TypeManager::sizeOf(" << type.toString() << ")");

	unsigned int size = 0;
	if (type.isPointer()){
		size = POINTER_SIZE;
	}else{
		string typeName = type.getBaseType();
		if (typeName == "void"){
			size = VOID_SIZE;
		}else if (typeName == "int"){
			size = INT_SIZE;
		}else if (typeName == "char"){
			size = CHAR_SIZE;
		}else if (typeName == "bool"){
			size = BOOL_SIZE;
		}else if (typeName == "long"){
			size = LONG_SIZE;
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

bool TypeManager::canConvert(const Type& from, const Type& to) const{
	if (isPrimitive(from) && isPrimitive(to)){
		if (sizeOf(from) > 0 || sizeOf(to) == 0){
			return true;
		}
	}
	return false;
}

bool TypeManager::typeExists(const string& typeName) const{
	return (typeName == "void") || (typeName == "int")
		|| (typeName == "char") || (typeName == "bool")
		|| (typeName == "long");
}

void TypeManager::clear(){
	//remove class and struct definitions
}