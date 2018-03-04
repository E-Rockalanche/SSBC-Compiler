#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "Lang.hpp"
#include "Scanner.hpp"
#include "Token.hpp"
#include <vector>
using namespace std;

class Tokenizer{
public:
	void setLang(Lang* lang);
	vector<Token>* tokenize(const string filename, vector<Token>* tokens = NULL);
	int errors();

private:
	Scanner scanner;
	vector<Token>* tokens;
	Lang* lang;
	int row;
	int col;
	int numErrors;

	void readToken();
	void skipWhiteSpace();
};

#endif