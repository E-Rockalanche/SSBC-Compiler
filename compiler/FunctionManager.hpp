#ifndef FUNCTION_MANAGER
#define FUNCTION_MANAGER

#include "FunctionSignature.hpp"
#include <vector>
#include <stdexcept>
using namespace std;

class FunctionManager{
public:
	bool functionExists(const FunctionSignature& function) const;
	bool addFunction(FunctionSignature function);
	Type getReturnType(const FunctionSignature& function) const;
	void clear();
private:
	vector<FunctionSignature> functions;
};

#endif