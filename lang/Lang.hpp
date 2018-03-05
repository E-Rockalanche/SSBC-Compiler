#ifndef LANG_HPP
#define LANG_HPP

#include <string>
using namespace std;

#define INVALID_TOKEN (-1)
class Lang{
public:
	Lang(){}
	virtual ~Lang(){};
	virtual int getTokenType(const string& str){
		throw(str);
		return INVALID_TOKEN;
	}
};

#endif