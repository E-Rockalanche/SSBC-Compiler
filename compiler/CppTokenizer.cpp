#include "CppTokenizer.hpp"
#include <iostream>
#include <cctype>
using namespace std;

//#define DEBUG true
#include "Debug.hpp"

CppTokenizer::CppTokenizer(){
	keywords["false"] = CppLang::FALSE;
	keywords["true"] = CppLang::TRUE;

	keywords["enum"] = CppLang::ENUM;
	keywords["union"] = CppLang::UNION;
	keywords["const"] = CppLang::CONST;
	keywords["typedef"] = CppLang::TYPEDEF;
	keywords["signed"] = CppLang::SIGNED;
	keywords["unsigned"] = CppLang::UNSIGNED;
	keywords["struct"] = CppLang::STRUCT;
	keywords["class"] = CppLang::CLASS;
	keywords["static"] = CppLang::STATIC;
	keywords["public"] = CppLang::PUBLIC;
	keywords["private"] = CppLang::PRIVATE;
	keywords["protected"] = CppLang::PROTECTED;

	keywords["break"] = CppLang::BREAK;
	keywords["else"] = CppLang::ELSE;
	keywords["switch"] = CppLang::SWITCH;
	keywords["case"] = CppLang::CASE;
	keywords["extern"] = CppLang::EXTERN;
	keywords["return"] = CppLang::RETURN;
	keywords["continue"] = CppLang::CONTINUE;
	keywords["for"] = CppLang::FOR;
	keywords["default"] = CppLang::DEFAULT;
	keywords["sizeof"] = CppLang::SIZEOF;
	keywords["volatile"] = CppLang::VOLATILE;
	keywords["do"] = CppLang::DO;
	keywords["if"] = CppLang::IF;
	keywords["while"] = CppLang::WHILE;
	keywords["delete"] = CppLang::DELETE;
	keywords["inline"] = CppLang::INLINE;
	keywords["namespace"] = CppLang::NAMESPACE;
	keywords["new"] = CppLang::NEW;
	keywords["operator"] = CppLang::OPERATOR;
	keywords["template"] = CppLang::TEMPLATE;
	keywords["this"] = CppLang::THIS;
	keywords["typename"] = CppLang::TYPENAME;
	keywords["virtual"] = CppLang::VIRTUAL;
	keywords["exit"] = CppLang::EXIT;
}

bool CppTokenizer::tokenize(string filename, vector<Token>& t){
	tokens = &t;
	scanner.open(filename);
	if (scanner.fail()){
		return false;
	}
	numErrors = 0;
	while(!scanner.eof()){
		addToken();
	}
	scanner.close();
	return (numErrors == 0);
}

void CppTokenizer::skipWhiteSpace(){
	while(isspace(scanner.peek())){
		scanner.get();
	}
}

void CppTokenizer::addToken(){
	skipWhiteSpace();
	
	if(scanner.eof()){
		return;
	}

	row = scanner.getRow();
	col = scanner.getCol();

	char c = scanner.get();
	if (isalpha(c) || c == '_'){
		scanner.unget();
		parseIdentifier();
	}else if (isdigit(c)){
		scanner.unget();
		parseInteger();
	}else{
		string str;
		CppLang::Token type;
		switch(c){
			case '"':
				parseString();
				return;
			case '\'':
				parseCharacter();
				return;
			case '[':
				str += c;
				type = CppLang::OPEN_BRACKET;
				break;
			case ']':
				str += c;
				type = CppLang::CLOSE_BRACKET;
				break;
			case '(':
				str += c;
				type = CppLang::OPEN_PAREN;
				break;
			case ')':
				str += c;
				type = CppLang::CLOSE_PAREN;
				break;
			case '{':
				str += c;
				type = CppLang::OPEN_BRACE;
				break;
			case '}':
				str += c;
				type = CppLang::CLOSE_BRACE;
				break;
			case ',':
				str += c;
				type = CppLang::COMMA;
				break;
			case ';':
				str += c;
				type = CppLang::SEMICOLON;
				break;
			case ':':
				str += c;
				type = CppLang::COLON;
				c = scanner.peek();
				if (c == ':'){
					str += scanner.get();
					type = CppLang::SCOPE;
				}
				break;
			case '*':
				str += c;
				type = CppLang::ASTERISK;
				break;
			case '+':
				str += c;
				type = CppLang::ADD;
				c = scanner.peek();
				if (c ==  '+'){
					str += scanner.get();
					type = CppLang::INC;
				}
				break;
			case '-':
				str += c;
				type = CppLang::SUB;
				c = scanner.peek();
				if (c ==  '-'){
					str += scanner.get();
					type = CppLang::DEC;
				}else if (c == '>'){
					str += scanner.get();
					type = CppLang::ARROW;
				}
				break;
			case '/':
				str += c;
				type = CppLang::DIV;
				c = scanner.peek();
				if (c ==  '/'){
					parseComment();
					return;
				}else if (c == '*'){
					parseCommentBlock();
					return;
				}
				break;
			case '%':
				str += c;
				type = CppLang::MOD;
				break;
			case '=':
				str += c;
				type = CppLang::ASSIGN;
				c = scanner.peek();
				if (c == '='){
					str += scanner.get();
					type = CppLang::EQUALS;
				}
				break;
			case '!':
				str += c;
				type = CppLang::NOT;
				c = scanner.peek();
				if (c == '='){
					str += scanner.get();
					type = CppLang::NOT_EQUALS;
				}
				break;
			case '>':
				str += c;
				type = CppLang::GREATER;
				c = scanner.peek();
				if (c == '='){
					str += scanner.get();
					type = CppLang::GREATER_EQUALS;
				}else if (c == '>'){
					str += scanner.get();
					type = CppLang::SHIFT_RIGHT;
				}
				break;
			case '<':
				str += c;
				type = CppLang::LESSER;
				c = scanner.peek();
				if (c == '='){
					str += scanner.get();
					type = CppLang::LESSER_EQUALS;
				}else if (c == '<'){
					str += scanner.get();
					type = CppLang::SHIFT_LEFT;
				}
				break;
			case '&':
				str += c;
				type = CppLang::AMPERSAND;
				c = scanner.peek();
				if (c == '&'){
					str += scanner.get();
					type = CppLang::AND;
				}
				break;
			case '|':
				str += c;
				type = CppLang::BIT_OR;
				c = scanner.peek();
				if (c == '|'){
					str += scanner.get();
					type = CppLang::OR;
				}
				break;
			case '^':
				str += c;
				type = CppLang::BIT_XOR;
				break;
			case '~':
				str += c;
				type = CppLang::TILDE;
				break;
			case '?':
				str += c;
				type = CppLang::CONDITION;
				break;
			case '.':
				str += c;
				type = CppLang::MEMBER;
				break;
			default:
				if (c == 0){
					dout("found END OF FILE");
					return;
				}
				str += c;
				type = CppLang::INVALID;
		}
		pushToken(Token(type, str, row, col));
	}
}

void CppTokenizer::parseIdentifier(){
	string str;
	char c = scanner.peek();
	while(isalnum(c) || c == '_'){
		str += scanner.get();
		c = scanner.peek();
	}
	CppLang::Token type = CppLang::IDENTIFIER;

	if (keywords.find(str) != keywords.end()){
		type = (CppLang::Token)keywords[str];
	}

	pushToken(Token(type, str, row, col));
}

void CppTokenizer::parseInteger(){
	string str;
	char c = scanner.peek();
	while(isalnum(c) || c == '_'){
		str += scanner.get();
		c = scanner.peek();
	}
	CppLang::Token type;
	if (regex_match(str, regex("^[1-9][0-9]*[lL]?$"))){
		type = CppLang::DECIMAL;
	}else if (regex_match(str, regex("^0x[0-9a-fA-F]+$"))){
		type = CppLang::HEXADECIMAL;
	}else if (regex_match(str, regex("^0[0-7]*$"))){
		type = CppLang::OCTAL;
	}else if (regex_match(str, regex("^0b[01]+$"))){
		type = CppLang::BINARY;
	}else{
		type = CppLang::INVALID;
	}
	pushToken(Token(type, str, row, col));
}

void CppTokenizer::parseString(){
	string str = "\"";
	char c = scanner.peek();
	char last = 'a';//arbitrary
	while(c != '"' || last == '\\'){
		last = c;
		str += scanner.get();
		c = scanner.peek();
	}
	str += '"';
	pushToken(Token(CppLang::STRING, str, row, col));
}

void CppTokenizer::parseCharacter(){
	string str = "'";
	char c = scanner.peek();
	char last = 'a';//arbitrary
	while(c != '\'' || last == '\\'){
		last = c;
		str += scanner.get();
		c = scanner.peek();
	}
	str += '\'';
	CppLang::Token type;
	if (regex_match(str, regex("'([^\\\\']|(\\\\.))'"))){
		type = CppLang::CHARACTER;
	}else{
		type = CppLang::INVALID;
	}
	pushToken(Token(type, str, row, col));
}

void CppTokenizer::parseComment(){
	string str;
	char c = scanner.peek();
	while(c != '\n' && !scanner.eof()){
		str += scanner.get();
		c = scanner.peek();
	}
}

void CppTokenizer::parseCommentBlock(){
	string str;
	char last = 'a';
	char c = scanner.peek();
	while((c != '/' || last != '*') && !scanner.eof()){
		last = c;
		str += scanner.get();
		c = scanner.peek();
	}
}

void CppTokenizer::printTokenError(Token token){
	cout << "Error: Invalid token " << token.value() << " at line "
		<< token.row() << ", column " << token.col() << '\n';
	numErrors++;
}

void CppTokenizer::pushToken(Token token){
	if (token.type() == CppLang::INVALID){
		printTokenError(token);
	}
	tokens->push_back(token);
	dout("[" << token.type() << "] " << token.value());
}

unsigned int CppTokenizer::errors(){
	return numErrors;
}