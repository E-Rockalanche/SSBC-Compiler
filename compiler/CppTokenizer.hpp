#ifndef CPP_TOKENIZER
#define CPP_TOKENIZER

#include "CppLang.hpp"
#include "Token.hpp"
#include "Scanner.hpp"
#include <vector>
#include <regex>
#include <string>
using namespace std;

class CppTokenizer{
public:
	CppTokenizer();
	bool tokenize(string filename, vector<Token>& t);
	unsigned int errors();
private:
	vector<Token>* tokens;
	map<string, int> keywords;
	Scanner scanner;
	int row;
	int col;
	unsigned int numErrors;

	void addToken();
	void pushToken(Token token);
	void skipWhiteSpace();
	void parseIdentifier();
	void parseInteger();
	void parseString();
	void parseCharacter();
	void parseComment();
	void parseCommentBlock();
	void printTokenError(Token token);
};

#endif