#include "CppLang.hpp"

CppLang::CppLang(){
	define(INT, "int");
	define(STRUCT, "struct");
	define(BREAK, "break");
	define(ELSE, "else");
	define(LONG, "long");
	define(SWITCH, "switch");
	define(CASE, "case");
	define(ENUM, "enum");
	define(TYPEDEF, "typedef");
	define(CHAR, "char");
	define(EXTERN, "extern");
	define(RETURN, "return");
	define(UNION, "union");
	define(CONST, "const");
	define(UNSIGNED, "unsigned");
	define(CONTINUE, "continue");
	define(FOR, "for");
	define(SIGNED, "signed");
	define(VOID, "void");
	define(DEFAULT, "default");
	define(SIZEOF, "sizeof");
	define(VOLATILE, "volatile");
	define(DO, "do");
	define(IF, "if");
	define(STATIC, "static");
	define(WHILE, "while");
	define(BOOL, "bool");
	define(CLASS, "class");
	define(DELETE, "delete");
	define(FALSE, "false");
	define(INLINE, "inline");
	define(NAMESPACE, "namespace");
	define(NEW, "new");
	define(OPERATOR, "operator");
	define(PRIVATE, "private");
	define(PROTECTED, "protected");
	define(PUBLIC, "public");
	define(TEMPLATE, "template");
	define(THIS, "this");
	define(TRUE, "true");
	define(TYPENAME, "typename");
	define(VIRTUAL, "virtual");
	define(IDENTIFIER, "[a-zA-Z_]+[a-zA-Z0-9_]*");
	define(HEXADECIMAL, "0x[0-9a-fA-F]+");
	define(DECIMAL, "[-+]?[1-9][0-9]*");
	define(OCTAL, "0[0-7]*");
	define(BINARY, "0b[01]+");
	define(CHAR,   "'([^\\\\']|(\\\\.))'");
	define(STRING, "\"([^\\\\\"]|(\\\\.))*\"");
	define(COMMENT, "//[ -~\\t]*(\\n)?");
	define(COMMENT_BLOCK, "/\\*[ -~\\t\\n\\r\\f]*\\*/");
	define(OPEN_BRACKET, "\\[");
	define(CLOSE_BRACKET, "\\]");
	define(OPEN_PAREN, "\\(");
	define(CLOSE_PAREN, "\\)");
	define(OPEN_BRACE, "\\{");
	define(CLOSE_BRACE, "\\}");
	define(COMMA, ",");
	define(SEMICOLON, ";");
	define(COLON, ":");
	define(ASTERISK, "\\*");
	define(DIRECTIVE, "#[ -~\\t]*(\\n)?");
	define(PLUS, "\\+");
	define(MINUS, "-");
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
	define(BIT_NOT, "~");
	define(SHIFT_LEFT, "<<");
	define(SHIFT_RIGHT, ">>");
	define(ASSIGN, "=");
	define(CONDITION, "\\?");
	define(ARROW, "->");
	define(PERIOD, "\\.");
	define(SCOPE, "::");
}

CppLang::~CppLang(){
}

int CppLang::getTokenType(const string& str){
	for(unsigned int i = 0; i < NUM_TOKENS; i++){
		if (regex_match(str, expressions[i])){
			return i;
		}
	}
	return INVALID_TOKEN;
}

void CppLang::define(Token token, string regExp){
	expressions[token] = regex("^" + regExp + "$");
}