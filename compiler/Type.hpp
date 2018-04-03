#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include "Assert.hpp"
using namespace std;

class Type{
public:
	Type();
	Type(string name, bool constant = false);
	Type& addPointer(bool constant = false);
	bool isConstant() const;
	bool isPointer() const;
	Type dereference() const;
	bool canConvertConstantsTo(const Type& other) const;
	bool isDefined() const;
	string getBaseType() const;
	string toString() const;
	string toLabel() const;
	bool operator==(const Type& other) const;
	bool operator!=(const Type& other) const;
private:
	bool defined;
	string name;
	bool constant;
	vector<bool> pointers;//booleans tell if each pointer is constant
};

#endif