#ifndef SSBC_TOKENIZER_HPP
#define SSBC_TOKENIZER_HPP

#include "Scanner.hpp"
#include "Token.hpp"
#include <vector>
using namespace std;

class SSBCTokenizer{
public:
	bool tokenize(string filename, vector<Token>& t);
	int errors();

private:
	Scanner scanner;
	vector<Token>* tokens;
	int row;
	int col;
	int numErrors;

	void skipWhiteSpace();
	Token getToken();
	Token getIdentifier();
	Token getInteger();
	Token getHexadecimal();
	Token getDecimal();
	Token getOctal();
	Token getBinary();
	Token getDirective();
	Token getCharacter();
	Token getString();
	Token getComment();
};

#endif

