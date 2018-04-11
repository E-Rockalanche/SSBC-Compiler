#ifndef LANG_HPP
#define LANG_HPP

#include <string>
#include "Assert.hpp"
using namespace std;

#define INVALID_TOKEN (-1)
class Lang{
public:
	Lang(){}
	virtual ~Lang(){};
	virtual int getTokenType(const string& str){
		assert(false, "Abstract call on Lang()");
		return -1;
	}
};

#endif