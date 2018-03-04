#include "Tokenizer.hpp"
#include "Debug.hpp"
#include "Assert.hpp"

void Tokenizer::setLang(Lang* lang){
	assert(lang != NULL, "Lang is NULL");
	this->lang = lang;
}

vector<Token>* Tokenizer::tokenize(const string filename, vector<Token>* tokens){
	if (tokens == NULL){
		tokens = new vector<Token>();
	}else{
		this->tokens = tokens;
	}

	scanner.open(filename);
	assert(!scanner.fail(), "Cannot open " + filename);
	
	while(!scanner.eof()){
		readToken();
	}

	scanner.close();

	return tokens;
}

void Tokenizer::readToken(){
	skipWhiteSpace();

	if (scanner.eof()){
		dout("End of file");
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