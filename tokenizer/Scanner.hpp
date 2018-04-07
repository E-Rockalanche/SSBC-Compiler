#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <fstream>
using namespace std;

//scanner class gets one character at a time from a file
//and keeps track of file row and column

class Scanner{
public:
	Scanner();
	Scanner(string filename);
	~Scanner();
	bool open(string filename);
	void close();
	bool fail();
	bool eof();
	char get();
	char peek();
	void unget();
	int getRow();
	int getCol();
private:
	ifstream fin;
	int row, lastRow;
	int col, lastCol;
	bool ungetted;
	char lastChar;
};

#endif