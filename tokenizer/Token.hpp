#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
using namespace std;

class Token{
public:
	Token(int t, string v, int r, int c){
		_type = t;
		_value = v;
		_row = r;
		_col = c;
	}
	int type(){return _type;}
	string value(){return _value;}
	int row(){return _row;}
	int col(){return _col;}
private:
	int _type;
	string _value;
	int _row;
	int _col;
};

#endif