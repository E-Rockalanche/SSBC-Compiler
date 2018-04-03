#include "CppLang.hpp"
#include "Debug.hpp"

CppLang::CppLang(){
	dout("CppLang::initializing");
	//literals
	define(FALSE, "false");
	define(TRUE, "true");
	define(HEXADECIMAL, "0x[0-9a-fA-F]+");
	define(DECIMAL, "[-+]?[1-9][0-9]*");
	define(OCTAL, "0[0-7]*");
	define(BINARY, "0b[01]+");
	define(CHARACTER,   "'([^\\\\']|(\\\\.))'");
	define(STRING, "\"([^\\\\\"]|(\\\\.))*\"");

	//data type stuff
	define(UNION, "union");
	define(CONST, "const");
	define(SIGNED, "signed");
	define(UNSIGNED, "unsigned");
	define(STRUCT, "struct");
	define(STATIC, "static");
	/*
	define(INT, "int");
	define(LONG, "long");
	define(CHAR, "char");
	define(BOOL, "bool");
	define(VOID, "void");
	*/

	//class stuff
	define(PRIVATE, "private");
	define(PROTECTED, "protected");
	define(PUBLIC, "public");

	//keywords
	define(BREAK, "break");
	define(ELSE, "else");
	define(SWITCH, "switch");
	define(CASE, "case");
	define(ENUM, "enum");
	define(TYPEDEF, "typedef");
	define(EXTERN, "extern");
	define(RETURN, "return");
	define(CONTINUE, "continue");
	define(FOR, "for");
	define(DEFAULT, "default");
	define(SIZEOF, "sizeof");
	define(VOLATILE, "volatile");
	define(DO, "do");
	define(IF, "if");
	define(WHILE, "while");
	define(CLASS, "class");
	define(DELETE, "delete");
	define(INLINE, "inline");
	define(NAMESPACE, "namespace");
	define(NEW, "new");
	define(OPERATOR, "operator");
	define(TEMPLATE, "template");
	define(THIS, "this");
	define(TYPENAME, "typename");
	define(VIRTUAL, "virtual");
	define(IDENTIFIER, "[a-zA-Z_]+[a-zA-Z0-9_]*");

	//delimeters
	define(OPEN_BRACKET, "\\[");
	define(CLOSE_BRACKET, "\\]");
	define(OPEN_PAREN, "\\(");
	define(CLOSE_PAREN, "\\)");
	define(OPEN_BRACE, "\\{");
	define(CLOSE_BRACE, "\\}");
	define(COMMA, ",");
	define(SEMICOLON, ";");
	define(COLON, ":");
	define(SCOPE, "::");

	//operators
	define(ASTERISK, "\\*");
	define(ADD, "\\+");
	define(SUB, "-");
	define(DIV, "/");
	define(MOD, "\%");
	define(INC, "\\+\\+");
	define(DEC, "--");
	define(EQUALS, "==");
	define(NOT_EQUALS, "!=");
	define(GREATER, ">");
	define(LESSER, "<");
	define(GREATER_EQUALS, ">=");
	define(LESSER_EQUALS, "<=");
	define(AND, "&&");
	define(OR, "\\|\\|");
	define(NOT, "!");
	define(AMPERSAND, "&");
	define(BIT_OR, "\\|");
	define(BIT_XOR, "\\^");
	define(TILDE, "~");
	define(SHIFT_LEFT, "<<");
	define(SHIFT_RIGHT, ">>");
	define(CONDITION, "\\?");
	define(ARROW, "->");
	define(PERIOD, "\\.");

	//assignment operators
	define(ASSIGN, "=");
	/*
	define(ASSIGN, "\\+=");
	define(ASSIGN, "-=");
	define(ASSIGN, "\\*=");
	define(ASSIGN, "/=");
	define(ASSIGN, "&=");
	define(ASSIGN, "\\|=");
	define(ASSIGN, "^=");
	define(ASSIGN, ">>=");
	define(ASSIGN, "<<=");
	*/

	define(COMMENT, "//[ -~\\t]*(\\n)?");
	define(COMMENT_BLOCK, "/\\*[ -~\\t\\n\\r\\f]*\\*/");
	define(DIRECTIVE, "#[ -~\\t]*(\\n)?");
}

CppLang::~CppLang(){
}

int CppLang::getTokenType(const string& str){
	for(unsigned int i = 0; i < NUM_TOKENS; i++){
		if (regex_match(str, expressions[i])){
			return (int)i;
		}
	}
	return INVALID_TOKEN;
}

void CppLang::define(Token token, string regExp){
	expressions[token] = regex("^" + regExp + "$");
}