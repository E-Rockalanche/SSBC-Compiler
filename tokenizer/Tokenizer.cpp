#include "Tokenizer.hpp"
#include "Debug.hpp"
#include "Assert.hpp"

void Tokenizer::setLang(Lang* lang){
	assert(lang != NULL, "Lang is NULL");
	this->lang = lang;
}

void Tokenizer::tokenize(const string& filename, vector<Token>* t){
	assert(t != NULL, "Given NULL vector of tokens");
	tokens = t;
	numErrors = 0;

	scanner.open(filename);
	assert(!scanner.fail(), "Cannot open " + filename);
	
	while(!scanner.eof()){
		readToken();
	}

	#if(DEBUG)
		for(unsigned int i = 0; i < tokens->size(); i++){
			Token token = tokens->at(i);
			cout << "[" << token.type() << "] " << token.value() << '\n';
		}
	#endif

	scanner.close();
}

void Tokenizer::readToken(){
	skipWhiteSpace();

	if (scanner.eof()){
		return;
	}

	row = scanner.getRow();
	col = scanner.getCol();
	string value = "";
	int type, nextType;

	nextType = lang->getTokenType(value + scanner.peek());
	do{
		type = nextType;
		value += scanner.get();
		nextType = lang->getTokenType(value + scanner.peek());
		if (scanner.eof()) break;
	}while(type == INVALID_TOKEN || nextType != INVALID_TOKEN);

	if (type == INVALID_TOKEN){
		numErrors++;
	}

	tokens->push_back(Token(type, value, row, col));
}

void Tokenizer::skipWhiteSpace(){
	while(isspace(scanner.peek())){
		scanner.get();
	}
}

int Tokenizer::errors(){
	return numErrors;
}