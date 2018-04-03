#include "FunctionManager.hpp"

bool FunctionManager::functionExists(const FunctionSignature& function) const{
	for(unsigned int i = 0; i < functions.size(); i++){
		if (functions[i] == function){
			return true;
		}
	}
	return false;
}

bool FunctionManager::addFunction(FunctionSignature function){
	if (!functionExists(function)){
		functions.push_back(function);
		return true;
	}
	return false;
}

Type FunctionManager::getReturnType(const FunctionSignature& function) const{
	for(unsigned int i = 0; i < functions.size(); i++){
		if (functions[i] == function){
			return functions[i].getReturnType();
		}
	}
	throw runtime_error("Function signature does not exist");
}

void FunctionManager::clear(){
	functions.clear();
}