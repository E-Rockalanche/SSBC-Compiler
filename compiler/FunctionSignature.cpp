#include "FunctionSignature.hpp"
#include <stdexcept>
using namespace std;

FunctionSignature::FunctionSignature(string name, Type returnType){
	this->name = name;
	this->returnType = returnType;
}

FunctionSignature& FunctionSignature::addParameter(Type type){
	parameters.push_back(type);
	return *this;
}

bool FunctionSignature::operator==(const FunctionSignature& other) const{
	if (parameters.size() != other.parameters.size() || (name != other.name)){
		return false;
	}
	for(unsigned int i = 0; i < parameters.size(); i++){
		if (parameters[i] != other.parameters[i]){
			return false;
		}
	}
	return true;
}

bool FunctionSignature::operator!=(const FunctionSignature& other) const{
	return !(*this == other);
}

unsigned int FunctionSignature::size() const{
	return parameters.size();
}

const Type& FunctionSignature::operator[](unsigned int index) const{
	if (index >= parameters.size()){
		throw out_of_range("FunctionSignature parameter index out of range");
	}
	return parameters[index];
}

const Type& FunctionSignature::getReturnType() const{
	return returnType;
}

string FunctionSignature::toString() const{
	string str = returnType.toString() + " " + name + "(";
	for(unsigned int i = 0; i < parameters.size(); i++){
		if (i > 0){
			str += ", ";
		}
		str += parameters[i].toString();
	}
	return str + ")";
}

string FunctionSignature::toLabel() const{
	string str = returnType.toLabel() + name;
	for(unsigned int i = 0; i < parameters.size(); i++){
		str += parameters[i].toLabel();
	}
	return str;
}