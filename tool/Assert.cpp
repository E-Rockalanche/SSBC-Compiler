#include "Assert.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void assert(bool expression, const char* message){
	if (!expression){
		cout << "Assert: " << message << '\n';
		exit(EXIT_FAILURE);
	}
}

void assert(bool expression, const string message){
	if (!expression){
		cout << "Assert: " << message << '\n';
		exit(EXIT_FAILURE);
	}
}