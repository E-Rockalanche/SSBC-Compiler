#ifndef FUNCTION_MANAGER
#define FUNCTION_MANAGER

#include "FunctionSignature.hpp"
#include <vector>
#include <stdexcept>
using namespace std;

class FunctionManager{
public:
	bool addFunction(FunctionSignature function);
	FunctionSignature findMatch(const FunctionSignature& function);
	void clear();
	void dump();
private:
	vector<FunctionSignature> functions;
};

#endif