#ifndef FUNCTION_SIGNATURE_HPP
#define FUNCTION_SIGNATURE_HPP

#include "Type.hpp"
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class FunctionSignature{
public:
	FunctionSignature();
	FunctionSignature(string name, Type returnType = Type(),
		bool implemented = false);
	FunctionSignature& addParameter(Type type, string name = "");
	FunctionSignature& setImplemented();
	bool operator==(const FunctionSignature& other) const;
	bool operator!=(const FunctionSignature& other) const;
	unsigned int numParams() const;
	Type getReturnType() const;
	Type getParamType(unsigned int index) const;
	string getParamName(unsigned int index) const;
	string toString() const;
	string toLabel() const;
	bool isDefined() const;
	bool isImplemented() const;

private:
	Type returnType;
	string name;
	vector<Type> paramTypes;
	vector<string> paramNames;
	bool implemented;
};

#endif