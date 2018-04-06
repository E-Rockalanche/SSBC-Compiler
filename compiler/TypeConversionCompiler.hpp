#ifndef TYPE_CONVERSION_COMPILER_HPP
#define TYPE_CONVERSION_COMPILER_HPP

#include "BaseCompiler.hpp"

class TypeConversionCompiler : public BaseCompiler {
public:
	static bool convert(const Type& from, const Type& to);
	static bool castToBool(Type from);
	static bool increaseSize(unsigned int fromSize, unsigned int toSize);
	static bool decreaseSize(unsigned int fromSize, unsigned int toSize);
};

#endif