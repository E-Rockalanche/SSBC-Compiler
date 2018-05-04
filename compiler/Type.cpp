#include "Type.hpp"

//create undefined type
Type::Type(){
	defined = false;
	constantBase = false;
	_isArray = false;
	_isReference = false;
	baseName = "'undefined'";
}

//create defined type
Type::Type(string baseName, bool constant){
	assert(baseName != "", "Empty baseName given to Type()");
	this->baseName = baseName;
	this->constantBase = constant;
	defined = true;
	_isArray = false;
	_isReference = false;
}

Type& Type::addPointer(bool constant){
	assert(isDefined(), "Cannot add pointers to " + toString());
	assert(!isReference(), "Cannot point to " + toString());
	assert(!isArray(), "Cannot point to " + toString());
	pointers.push_back(constant);
	return *this;
}

Type& Type::removePointer(){
	assert(isPointer() || isArray(), "Cannot remove pointer from " + toString());
	if (isReference()){
		_isReference = false;
	}
	if (isArray()){
		_isArray = false;
	}else{
		pointers.pop_back();
	}
	return *this;
}

Type& Type::reference(){
	assert(isDefined(), "Cannot reference " + toString());
	assert(!isReference(), "Cannot reference " + toString());
	_isReference = true;
	return *this;
}

Type& Type::dereference(){
	assert(isPointer(), "Cannot dereference " + toString());
	if (isReference()){
		_isReference = false;
	}
	return *this;
}

Type& Type::makeArray(unsigned int size, bool constant){
	assert(isDefined(), "Cannot make array of " + toString());
	assert(!isArray(), "Cannot make array of arrays");

	_isArray = true;
	arraySize = size;
	constantArray = constant;
	return *this;
}

Type& Type::convertArrayToPointer() {
	if (isArray()) {
		_isArray = false;
		addPointer(true);
	}
	return *this;
}

unsigned int Type::numPointers(){
	return pointers.size();
}

bool Type::isConstant() const{
	if (isPointer()){
		return pointers.back();
	} else {
		return constantBase;
	}
}

bool Type::isReference() const {
	return _isReference;
}

bool Type::isArray() const {
	return _isArray;
}

bool Type::isPointer() const {
	return (pointers.size() > 0);
}

bool Type::isDefined() const {
	return defined;
}

string Type::getBaseType() const {
	return baseName;
}

string Type::toString() const {
	string str;
	if (isDefined()){
		if (constantBase) str += "const ";
		str += baseName;
		for(unsigned int i = 0; i < pointers.size(); i++){
			str += " *";
			if (pointers[i]){
				str += " const";
			}
		}
		if (_isArray){
			str += "[" + to_string(arraySize) + "]";
		}
		if (_isReference){
			str += "&";
		}
	}else{
		str = "'undefined'";
	}
	return str;
}

string Type::toLabel() const {
	string str;
	if (isDefined()){
		//if (constantBase) str += "Const";
		str += baseName;
		for(unsigned int i = 0; i < pointers.size(); i++){
			str += "_Ptr";
			/*
			if (pointers[i]){
				str += "Const";
			}
			*/
		}
		if (_isArray){
			str += "_Array" + to_string(arraySize);
		}
		if (_isReference){
			str += "_Ref";
		}
	}else{
		throw runtime_error("Cannot convert undefined type to label");
	}
	return str;
}

bool Type::operator==(const Type& other) const {
	return ((pointers.size() == other.pointers.size())
		&& (baseName == other.baseName)
		&& (_isReference == other._isReference)
		&& (_isArray == other._isArray));
}

bool Type::operator!=(const Type& other) const {
	return !(*this == other);
}

unsigned int Type::getArraySize(){
	assert(isArray(), toString() + " is not an array");
	return arraySize;
}