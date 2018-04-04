#include "Tokenizer.hpp"
#include <string>
#include <iostream>
using namespace std;

int main(const int argc, const char** argv){
	string filename;
	if (argc > 1){
		filename = argv[1];
	}else{
		cout << "usage is " << argv[0] << " <file>\n";
		return 0;
	}

	vector<Token> tokens;
	SSBCTokenizer tokenizer;
	tokenizer.tokenize(filename, tokens);

	for(unsigned int i = 0; i < tokens.size(); i++){
		Token token = tokens[i];
		cout << '[' << token.type() << "] " << token.value() << " ("
			<< token.row() << ", " << token.col() << ")\n";
	}

	cout << "errors: " << tokenizer.errors() << '\n';

	return 0;
}