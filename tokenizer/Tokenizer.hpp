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
	void tokenize(const string& filename, vector<Token>* t = NULL);
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