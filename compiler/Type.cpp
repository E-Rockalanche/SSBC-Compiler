#include "Type.hpp"

Type::Type(){
	defined = false;
	name = "'undefined'";
	constant = true;
}

Type::Type(string name, bool constant){
	this->name = name;
	this->constant = constant;
	defined = true;
}

Type& Type::addPointer(bool constant){
	pointers.push_back(constant);
	return *this;
}

bool Type::isConstant() const{
	if (pointers.size() > 0){
		return pointers.back();
	}else{
		return constant;
	}
}

bool Type::isPointer() const{
	return (pointers.size() > 0);
}

Type Type::dereference() const{
	assert(pointers.size() > 0, "Trying to dereference non-pointer type");
	Type t = *this;
	t.pointers.pop_back();
	return t;
}
	
bool Type::canConvertConstantsTo(const Type& other) const{
	assert(pointers.size() == other.pointers.size(),
		"Trying to compare constants on types with differing amount of \
pointers");
	if (pointers.size() == 0){
		return true;
	}
	for(int i = 0; i < (int)pointers.size()-1; i++){
		if (pointers[i] && !other.pointers[i])
			return false;
	}
	return true;
}

bool Type::isDefined() const{
	return defined;
}

string Type::getBaseType() const{
	return name;
}

string Type::toString() const{
	string str;
	if (isDefined()){
		if (constant) str += "const ";
		str += name;
		for(unsigned int i = 0; i < pointers.size(); i++){
			str += " *";
			if (pointers[i]){
				str += "const";
			}
		}
	}else{
		str = "'undefined'";
	}
	return str;
}

string Type::toLabel() const{
	string str;
	if (isDefined()){
		//if (constant) str += "Const";
		str += name;
		for(unsigned int i = 0; i < pointers.size(); i++){
			str += "Ptr";
			/*
			if (pointers[i]){
				str += "Const";
			}
			*/
		}
	}else{
		throw runtime_error("Cannot convert undefined type to label");
	}
	return str;
}

bool Type::operator==(const Type& other) const{
	return (pointers.size() == other.pointers.size() && name == other.name);
}

bool Type::operator!=(const Type& other) const{
	return !(*this == other);
}