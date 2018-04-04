#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
using namespace std;

class Token{
public:
	inline Token(){
		_type = -1;
		_row = -1;
		_col = -1;
		_value = "'undefined'";
	}
	inline Token(int t, string v, int r, int c){
		_type = t;
		_value = v;
		_row = r;
		_col = c;
	}
	inline int type(){return _type;}
	inline string value(){return _value;}
	inline int row(){return _row;}
	inline int col(){return _col;}
private:
	int _type;
	string _value;
	int _row;
	int _col;
};

#endif