#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include "Assert.hpp"
using namespace std;

class Type{
public:
	//set base type
	Type();
	Type(string name, bool constant = false);

	//modify type
	Type& addPointer(bool constant = false);
	Type& removePointer();
	Type& makeArray(unsigned int size, bool constant = false);
	Type& reference();
	Type& dereference();
	Type& convertArrayToPointer();

	//check attributes
	string getBaseType() const;
	unsigned int numPointers();
	unsigned int getArraySize();
	bool isDefined() const;
	bool isConstant() const;
	bool isPointer() const;
	bool isArray() const;
	bool isReference() const;

	//comparisons
	bool operator==(const Type& other) const;
	bool operator!=(const Type& other) const;

	string toString() const;
	string toLabel() const;
private:
	bool defined;
	
	string baseName;
	bool constantBase;

	//number os pointers and wether each is constant
	vector<bool> pointers;

	//is sequential array of data
	bool _isArray;
	bool constantArray;
	unsigned int arraySize;

	//is pointer to above type
	bool _isReference;
};

#endif