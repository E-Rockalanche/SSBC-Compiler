#include "Scanner.hpp"

//#define DEBUG true
#include "Debug.hpp"

Scanner::Scanner(){
}

Scanner::Scanner(string filename){
	open(filename);
}

Scanner::~Scanner(){
	close();
}

bool Scanner::open(string filename){
	fin.open(filename.c_str());
	ungetted = false;
	row = 1;
	col = 0;
	if (fin.fail()){
		cout << "Failed to open " << filename << '\n';
		return false;
	}
	return true;
}

void Scanner::close(){
	fin.close();
}

bool Scanner::fail(){
	return fin.fail();
}

bool Scanner::eof(){
	#if(DEBUG)
		if(fin.eof()) dout("END OF FILE");
	#endif
	return fin.eof();
}

char Scanner::get(){
	int c;
	if (fin.eof()){
		c = 0;
	}else{
		c = fin.get();
	}
	lastChar = c;
	ungetted = false;
	lastRow = row;
	lastCol = col;
	if (c == '\n'){
		row++;
		col = 1;
	}else{
		col++;
	}
	return c;
}

char Scanner::peek(){
	if (fin.eof()) return 0;
	return fin.peek();
}

void Scanner::unget(){
	if (!ungetted && lastChar != 0){
		fin.putback(lastChar);
		ungetted = true;
		row = lastRow;
		col = lastCol;
	}
}

int Scanner::getRow(){
	return row;
}

int Scanner::getCol(){
	return col;
}