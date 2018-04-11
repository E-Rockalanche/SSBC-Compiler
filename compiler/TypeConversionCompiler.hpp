#ifndef TYPE_CONVERSION_COMPILER_HPP
#define TYPE_CONVERSION_COMPILER_HPP

#include "BaseCompiler.hpp"

class TypeConversionCompiler : public BaseCompiler {
public:
	static bool convert(const Type& from, const Type& to,
		unsigned int tokenIndex);
	static bool convert(const Type& from, const Type& to);
	
private:
	static bool toVoid(Type from);
	static bool toBool(Type from);
	static bool toInt(Type from);
	static bool toLong(Type from);
	static bool toChar(Type from);
	static bool toPointer(Type from, Type to);
	static bool toReference(Type from, Type to);
	static bool toArray(Type from, Type to);
	static bool adjustSize(unsigned int fromSize, unsigned int toSize);
	static bool increaseSize(unsigned int fromSize, unsigned int toSize);
	static bool decreaseSize(unsigned int fromSize, unsigned int toSize);
};

#endif