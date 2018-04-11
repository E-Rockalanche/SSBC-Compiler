#include "FunctionManager.hpp"
#include "CompilerDebug.hpp"
#include <iostream>
using namespace std;

bool FunctionManager::addFunction(FunctionSignature function){
	dout("adding function " << function.toString());
	for(unsigned int i = 0; i < functions.size(); i++){
		if (functions[i] == function){
			if (!functions[i].isImplemented() && function.isImplemented()){
				dout("implemented prototype " << function.toString());
				functions[i] = function;
				return true;
			}else{
				dout("function " << function.toString() << " already exists");
				return false;
			}
		}
	}
	dout("added function " << function.toString());
	functions.push_back(function);
	return true;
}

FunctionSignature FunctionManager::findMatch(const FunctionSignature& function){
	dout("finding match for " << function.toString());
	for(unsigned int i = 0; i < functions.size(); i++){
		dout("trying " << functions[i].toString());
		if (functions[i] == function){
			return functions[i];
		}
	}
	dout("no match");
	return FunctionSignature();
}

void FunctionManager::clear(){
	functions.clear();
}

void FunctionManager::dump(){
	cout << "===== Function Manager =====\n";
	for(unsigned int i = 0; i < functions.size(); i++){
		cout << functions[i].toString() << '\n';
	}
	cout << "============================\n";
}