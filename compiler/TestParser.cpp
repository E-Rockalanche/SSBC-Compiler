#include <vector>
#include <iostream>
#include <string>
#include "Parser.hpp"
#include "Tokenizer.hpp"
#include "CppLang.hpp"
#include "Debug.hpp"
using namespace std;

int main(int argc, const char** argv){
	dout("~~~ PARSER TEST ~~~");
	if (argc < 2){
		cout << "Usage is " << argv[0] << " <file>\n";
		return 0;
	}
	string filename = argv[1];

	dout("tokenizing");
	Tokenizer tokenizer;
	tokenizer.setLang(new CppLang());
	vector<Token>* tokens = tokenizer.tokenize(filename);

	dout("parsing");
	Parser parser;
	parser.setTokens(tokens);
	Tree* root = parser.parse();

	if (root){
		delete root;
		cout << "Parse succeeded\n";
	}else{
		cout << "Parse failed\n";
	}

	return 0;
}