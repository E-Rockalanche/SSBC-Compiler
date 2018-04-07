#include "CppTokenizer.hpp"
#include "Token.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(const int argc, const char** argv){
	string file;
	if (argc == 1){
		cout << "file: ";
		cin >> file;
	}else{
		file = argv[1];
	}
	vector<Token> tokens;
	CppTokenizer tokenizer;
	tokenizer.tokenize(file, tokens);
	for(unsigned int i = 0; i < tokens.size(); i++){
		Token token = tokens[i];
		cout << "[" << token.type() << "] " << token.value() << '\n';
	}
}