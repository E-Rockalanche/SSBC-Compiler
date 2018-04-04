#include "SSBCLang.hpp"
#include "Tokenizer.hpp"
#include <cctype>
using namespace std;

#define DEBUG true
#include "Debug.hpp"

bool SSBCTokenizer::tokenize(string filename, vector<Token>& t){
	dout("tokenize(" << filename << ")");

	this->tokens = &t;

	if (!scanner.open(filename)){
		return false;
	}

	Token token;
	while(!scanner.eof()){
		token = getToken();
		#if(DEBUG)
			cout << '[' << token.type() << "] " << token.value() << '\n';
		#endif
		numErrors += (token.type() == SSBCLang::INVALID);
		tokens->push_back(token);
	}

	scanner.close();

	return (numErrors == 0);
}

int SSBCTokenizer::errors(){
	return numErrors;
}

void SSBCTokenizer::skipWhiteSpace(){
	while(isspace(scanner.peek())){
		scanner.get();
	}
}

Token SSBCTokenizer::getToken(){
	dout("getToken()");
	Token token;

	skipWhiteSpace();

	row = scanner.getRow();
	col = scanner.getCol();

	if (scanner.eof()){
		return Token(SSBCLang::EOT, "", row, col);
		dout("END OF FILE");
	}

	char c = scanner.peek();
	string str = "";

	if (isalpha(c) || c == '_'){
		token = getIdentifier();
	}else if (isdigit(c) || c == '-'){
		token = getInteger();
	}else{
		switch(c){
			case '.':
				token = getDirective();
				break;
			case '\'':
				token = getCharacter();
				break;
			case '"':
				token = getString();
				break;
			case '+':
				str += scanner.get();
				token = Token(SSBCLang::PLUS, str, row, col);
				break;
			case '/':
				token = getComment();
				break;
			case ':':
				str += scanner.get();
				token = Token(SSBCLang::COLON, str, row, col);
				break;
			case '>':
				str += scanner.get();
				token = Token(SSBCLang::LOW_BITS, str, row, col);
				break;
			case '<':
				str += scanner.get();
				token = Token(SSBCLang::HIGH_BITS, str, row, col);
				break;
			case '?':
				str += scanner.get();
				token = Token(SSBCLang::BLANK_ADDRESS, str, row, col);
				break;
			default:
				str += scanner.get();
				token = Token(SSBCLang::INVALID, str, row, col);
		}
	}
	return token;
}

Token SSBCTokenizer::getIdentifier(){
	dout("getIdentifier()");

	string str;
	str += scanner.get();
	char c = scanner.peek();
	while(isalnum(c) || c == '_'){
		str += scanner.get();
		c = scanner.peek();
	}
	SSBCLang::Token type;
	if (str == "noop"){
		type = SSBCLLang::NOOP;
	}else if (str == "halt"){
		type = SSBCLLang::HALT;
	}else if (str == "pushimm"){
		type = SSBCLLang::PUSHIMM;
	}else if (str == "pushext"){
		type = SSBCLLang::PUSHEXT;
	}else if (str == "popinh"){
		type = SSBCLLang::POPINH;
	}else if (str == "popext"){
		type = SSBCLLang::POPEXT;
	}else if (str == "jnz"){
		type = SSBCLLang::JNZ;
	}else if (str == "jnn"){
		type = SSBCLLang::JNN;
	}else if (str == "add"){
		type = SSBCLLang::ADD;
	}else if (str == "sub"){
		type = SSBCLLang::SUB;
	}else if (str == "nor"){
		type = SSBCLLang::NOR;
	}else{
		type = SSBCLang::IDENTIFIER;
	}
	return Token(type, str, row, col);
}

Token SSBCTokenizer::getInteger(){
	dout("getInteger()");
	Token token;
	char c = scanner.peek();
	if (c != '0'){
		token = getDecimal();
	}else{
		scanner.get();
		switch(scanner.get()){
			case 'x':
				token = getHexadecimal();
				break;
			case 'b':
				token = getBinary();
				break;
			default:
				scanner.unget();
				token = getOctal();
				break;
		}
	}
	return token;
}

Token SSBCTokenizer::getHexadecimal(){
	dout("getHexadecimal()");
	string str = "0x";
	while(isxdigit(scanner.peek())){
		str += scanner.get();
	}
	return Token(SSBCLang::HEXADECIMAL, str, row, col);
}

Token SSBCTokenizer::getDecimal(){
	dout("getDecimal()");
	string str;
	if (scanner.peek() == '-'){
		str = scanner.get();
	}
	while(isdigit(scanner.peek())){
		str += scanner.get();
	}
	return Token(SSBCLang::DECIMAL, str, row, col);
}

Token SSBCTokenizer::getOctal(){
	dout("getOctal()");
	string str = "0";
	while(scanner.peek() >= '0' && scanner.peek() <= '7'){
		str += scanner.get();
	}
	return Token(SSBCLang::OCTAL, str, row, col);
}

Token SSBCTokenizer::getBinary(){
	dout("getBinary()");
	string str = "0b";
	while(scanner.peek() == '0' || scanner.peek() == '1'){
		str += scanner.get();
	}
	return Token(SSBCLang::BINARY, str, row, col);
}

Token SSBCTokenizer::getDirective(){
	dout("getDirective()");
	string str;
	str += scanner.get();
	while(isalpha(scanner.peek())){
		str += scanner.get();
	}
	SSBCLang::Token type;
	if (str == ".start"){
		type = SSBCLang::START;
	}else if (str == ".global"){
		type = SSBCLang::GLOBAL;
	}else if (str == ".file"){
		type = SSBCLang::FILE;
	}else if (str == ".byte"){
		type = SSBCLang::BYTE;
	}else if (str == ".word"){
		type = SSBCLang::WORD;
	}else if (str == ".array"){
		type = SSBCLang::ARRAY;
	}else if (str == ".ascii"){
		type = SSBCLang::ASCII;
	}else if (str == ".asciz"){
		type = SSBCLang::ASCIZ;
	}else{
		type = SSBCLang::INVALID;
	}
	return Token(type, str, row, col);
}

Token SSBCTokenizer::getCharacter(){
	dout("getCharacter()");
	Token token;
	char c = scanner.get();
	char last;
	string str;
	str += c;
	do{
		if (scanner.eof()){
			return Token(SSBCLang::INVALID, str, row, col);
		}
		last = c;
		c = scanner.get();
		str += c;
	}while(c != '\'' || last == '\\');

	if (str.size() < 3 || str.size() > 4){
		token = Token(SSBCLang::INVALID, str, row, col);
	}else if ((str.size() == 4) && (str[1] != '\\')){
		token = Token(SSBCLang::INVALID, str, row, col);
	}else{
		token = Token(SSBCLang::CHAR, str, row, col);
	}
	return token;
}

Token SSBCTokenizer::getString(){
	dout("getString()");
	char c = scanner.get();
	char last;
	string str;
	str += c;
	do{
		if (scanner.eof()){
			return Token(SSBCLang::INVALID, str, row, col);
		}
		last = c;
		c = scanner.get();
		str += c;
	}while(c != '"' || last == '\\');
	return Token(SSBCLang::STRING, str, row, col);
}

Token SSBCTokenizer::getComment(){
	dout("getComment()");
	string str;
	str += scanner.get();
	if (scanner.peek() == '/'){
		str += scanner.get();
		while(scanner.peek() != '\n'){
			if (scanner.eof()){
				return Token(SSBCLang::INVALID, str, row, col);
			}
			str += scanner.get();
		}
	}else if(scanner.peek() == '*'){
		char c, last = 'a';//arbitrary value
		while(!(c == '/' && last == '*')){
			if (scanner.eof()){
				break;
			}
			last = c;
			c = scanner.get();
		}
	}else{
		return Token(SSBCLang::INVALID, str, row, col);
	}
	return Token(SSBCLang::COMMENT, str, row, col);
}