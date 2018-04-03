#ifndef TYPE_MANAGER_HPP
#define TYPE_MANAGER_HPP

#include <stdexcept>
#include "Type.hpp"
using namespace std;

#define VOID_SIZE 0
#define INT_SIZE 1
#define CHAR_SIZE 1
#define BOOL_SIZE 1
#define LONG_SIZE 2
#define POINTER_SIZE 2

class TypeManager{
public:
	unsigned int sizeOf(const Type& type) const;
	bool isPrimitive(const Type& type) const;
	bool canConvert(const Type& from, const Type& to) const;
	bool typeExists(const string& typeName) const;
	void clear();
private:
	//class & struct definitions
};

#endif