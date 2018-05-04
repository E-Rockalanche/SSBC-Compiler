#include "BaseStatementCompiler.hpp"

bool BaseStatementCompiler::endsStatementSequence() {
	return false;
}

bool BaseStatementCompiler::returnsFromFunction() {
	return false;
}