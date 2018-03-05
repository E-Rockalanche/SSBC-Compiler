#ifndef CPP_LANG
#define CPP_LANG

#include "Lang.hpp"
#include <regex>
using namespace std;

class CppLang : public Lang{
public:
	enum Token{
		//keywords
		INT,
		STRUCT,
		BREAK,
		ELSE,
		LONG,
		SWITCH,
		CASE,
		ENUM,
		TYPEDEF,
		CHAR,
		EXTERN,
		RETURN,
		UNION,
		CONST,
		UNSIGNED,
		CONTINUE,
		FOR,
		SIGNED,
		VOID,
		DEFAULT,
		SIZEOF,
		VOLATILE,
		DO,
		IF,
		STATIC,
		WHILE,
		BOOL,
		CLASS,
		DELETE,
		FALSE,
		INLINE,
		NAMESPACE,
		NEW,
		OPERATOR,
		PRIVATE,
		PROTECTED,
		PUBLIC,
		TEMPLATE,
		THIS,
		TRUE,
		TYPENAME,
		VIRTUAL,

		IDENTIFIER,

		//literals
		HEXADECIMAL,
		DECIMAL,
		OCTAL,
		BINARY,
		CHARACTER,
		STRING,

		//other
		COMMENT,
		COMMENT_BLOCK,

		//special symbols
		OPEN_BRACKET,
		CLOSE_BRACKET,
		OPEN_PAREN,
		CLOSE_PAREN,
		OPEN_BRACE,
		CLOSE_BRACE,
		COMMA,
		SEMICOLON,
		COLON,
		ASTERISK,
		DIRECTIVE,

		//operators
		PLUS,
		MINUS,
		DIV,
		MOD,
		INC,
		DEC,
		EQUALS,
		NOT_EQUALS,
		GREATER,
		LESSER,
		GREATER_EQUALS,
		LESSER_EQUALS,
		AND,
		OR,
		NOT,
		AMPERSAND,
		BIT_OR,
		BIT_XOR,
		BIT_NOT,
		SHIFT_LEFT,
		SHIFT_RIGHT,
		ASSIGN,
		CONDITION,
		ARROW,
		PERIOD,
		SCOPE,

		NUM_TOKENS,

		EOT
	};

	CppLang();
	~CppLang();
	int getTokenType(const string& str);

private:
	regex expressions[NUM_TOKENS];

	void define(Token token, string regExp);
};

#define CASE_INTEGER \
	case CppLang::HEXADECIMAL:\
	case CppLang::DECIMAL:\
	case CppLang::OCTAL:\
	case CppLang::BINARY:

#endif