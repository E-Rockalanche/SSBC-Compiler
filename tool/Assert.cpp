#include "Assert.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void assert(bool expression, const string message){
	if (!expression){
		cout << "Error: " << message << '\n';
		exit(EXIT_FAILURE);
	}
}