#ifndef COMPILER_DATA_HPP
#define COMPILER_DATA_HPP

#include "BaseCompiler.hpp"
#include "ScopeTable.hpp"
#include "TypeManager.hpp"
#include "FunctionManager.hpp"
#include "BreakManager.hpp"

class CompilerData : public BaseCompiler {
protected:
	static ScopeTable scopeTable;
	static TypeManager typeManager;
	static FunctionManager functionManager;
	static BreakManager breakManager;
};

#endif