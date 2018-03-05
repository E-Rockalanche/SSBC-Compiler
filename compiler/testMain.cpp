#include "../tokenizer/Tokenizer.hpp"
#include "CppLang.hpp"
#include <iostream>
using namespace std;

int main(int argc, const char** argv){
	if (argc > 1){
		Tokenizer tokenizer;
		tokenizer.setLang(new CppLang());
		vector<Token> tokens;
		tokenizer.tokenize(argv[1], &tokens);
		for(unsigned int i = 0; i < tokens.size(); i++){
			cout << "[" << tokens[i].type() << "] " << tokens[i].value() << "\n";
		}
	}
}