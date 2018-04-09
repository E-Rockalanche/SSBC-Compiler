#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <string>
using namespace std;

void assert(bool expression, const char* message);
void assert(bool expression, const string message);

#endif