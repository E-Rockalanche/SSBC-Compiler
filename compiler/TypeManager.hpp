#ifndef TYPE_MANAGER_HPP
#define TYPE_MANAGER_HPP

#include <stdexcept>
#include "Type.hpp"
using namespace std;

#define VOID_SIZE 0

#define INT_SIZE 1
#define SSBC_INT_MAX 127
#define SSBC_INT_MIN (-128)

#define CHAR_SIZE 1
#define SSBC_CHAR_MAX 127
#define SSBC_CHAR_MIN (-128)

#define BOOL_SIZE 1
#define SSBC_BOOL_MAX 1
#define SSBC_BOOL_MIN 0

#define LONG_SIZE 2
#define SSBC_LONG_MAX 0x7fff
#define SSBC_LONG_MIN (-0x8000)

#define POINTER_SIZE 2
#define SSBC_PTR_MAX 0x7fff
#define SSBC_PTR_MIN (-0x8000)

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