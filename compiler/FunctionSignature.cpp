#include "FunctionSignature.hpp"
#include "Assert.hpp"
#include "CompilerDebug.hpp"
#include <stdexcept>
using namespace std;

FunctionSignature::FunctionSignature(){
	name = "";
	returnType = Type();
	implemented = false;
}

FunctionSignature::FunctionSignature(string name, Type returnType,
		bool implemented){
	assert(name != "", "Empty string given to FunctionSignature(string, Type)");
	this->name = name;
	this->returnType = returnType;
	this->implemented = implemented;
}

FunctionSignature& FunctionSignature::addParameter(Type type, string name){
	paramTypes.push_back(type);
	paramNames.push_back(name);
	return *this;
}

FunctionSignature& FunctionSignature::setImplemented(){
	implemented = true;
	return *this;
}

bool FunctionSignature::operator==(const FunctionSignature& other) const{
	dout(toString() << " == " << other.toString() << " ?");

	if (paramTypes.size() != other.paramTypes.size() || (name != other.name)){
		dout("# of params or function names are different");
		return false;
	}

	for(unsigned int i = 0; i < paramTypes.size(); i++){
		if (paramTypes[i] != other.paramTypes[i]){
			dout(paramTypes[i].toString() << " != "
				<< other.paramTypes[i].toString());
			return false;
		}
	}

	dout("signatures are the same");
	return true;
}

bool FunctionSignature::operator!=(const FunctionSignature& other) const{
	return !(*this == other);
}

unsigned int FunctionSignature::numParams() const{
	return paramTypes.size();
}

Type FunctionSignature::getParamType(unsigned int index) const{
	if (index >= paramTypes.size()){
		throw out_of_range("FunctionSignature parameter index out of range");
	}
	return paramTypes[index];
}

string FunctionSignature::getParamName(unsigned int index) const{
	if (index >= paramNames.size()){
		throw out_of_range("FunctionSignature parameter index out of range");
	}
	return paramNames[index];
}

Type FunctionSignature::getReturnType() const{
	return returnType;
}

string FunctionSignature::toString() const{
	string str;
	if (returnType.isDefined()){
		str = returnType.toString() + " ";
	}
	str += name + "(";
	for(unsigned int i = 0; i < paramTypes.size(); i++){
		if (i > 0){
			str += ", ";
		}
		str += paramTypes[i].toString();
	}
	return str + ")";
}

string FunctionSignature::toLabel() const{
	string str = returnType.toLabel() + name;
	for(unsigned int i = 0; i < paramTypes.size(); i++){
		str += paramTypes[i].toLabel();
	}
	return str;
}

bool FunctionSignature::isDefined() const {
	return (name != "" && returnType != Type());
}

bool FunctionSignature::isImplemented() const {
	return implemented;
}