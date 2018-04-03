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
	FunctionSignature(string name, Type returnType = Type());
	FunctionSignature& addParameter(Type type);
	bool operator==(const FunctionSignature& other) const;
	bool operator!=(const FunctionSignature& other) const;
	unsigned int size() const;
	const Type& getReturnType() const;
	const Type& operator[](unsigned int index) const;
	string toString() const;
	string toLabel() const;
private:
	Type returnType;
	string name;
	vector<Type> parameters;
};

#endif