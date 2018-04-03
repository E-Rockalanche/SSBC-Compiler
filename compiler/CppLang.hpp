#ifndef CPP_LANG
#define CPP_LANG

#include "Lang.hpp"
#include <regex>
using namespace std;

class CppLang : public Lang{
public:
	enum Token{
		//types
		/*
		VOID,
		INT,
		CHAR,
		BOOL,
		LONG,
		*/
		STRUCT,
		CLASS,
		UNION,
		
		//keywords
		BREAK,
		ELSE,
		SWITCH,
		CASE,
		ENUM,
		TYPEDEF,
		EXTERN,
		RETURN,
		CONST,
		UNSIGNED,
		CONTINUE,
		FOR,
		SIGNED,
		DEFAULT,
		SIZEOF,
		VOLATILE,
		DO,
		IF,
		STATIC,
		WHILE,
		DELETE,
		INLINE,
		NAMESPACE,
		NEW,
		OPERATOR,
		PRIVATE,
		PROTECTED,
		PUBLIC,
		TEMPLATE,
		THIS,
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
		TRUE,
		FALSE,

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
		ADD,
		SUB,
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
		TILDE,
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
/*
#define CASE_PRIMITIVE\
	case CppLang::INT:\
	case CppLang::CHAR:\
	case CppLang::LONG:\
	case CppLang::VOID:\
	case CppLang::BOOL:
*/
#endif