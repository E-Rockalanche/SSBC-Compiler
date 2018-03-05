#ifndef SSBCLANG_HPP
#define SSBCLANG_HPP

#include "Lang.hpp"
#include <regex>
using namespace std;

class SSBCLang : public Lang{
public:
	enum Token{

		//native instructions
		NOOP,
		HALT,
		PUSHIMM,
		PUSHEXT,
		POPINH,
		POPEXT,
		JNZ,
		JNN,
		ADD,
		SUB,
		NOR,

		//extended instructions
		TEST,
		PUSHIMM16,
		PUSHEXT16,
		POPINH16,
		POPEXT16,
		JUMP,
		JSR,
		CLEAR,
		CLEARPSW,
		CLONE,
		OR,
		AND,
		NOT,
		NAND,
		COMPARE,
		INC,
		DEC,
		SWAP,
		MOVE,
		BTEST,
		BSET,
		BCLEAR,

		//directives
		START,
		GLOBAL,
		FILE,
		BYTE,
		WORD,
		ARRAY,
		ASCII,
		ASCIZ,

		//literals
		HEXADECIMAL,
		DECIMAL,
		OCTAL,
		BINARY,
		CHAR,
		STRING,

		//other
		COMMENT,
		COMMENT_BLOCK,
		IDENTIFIER,
		COLON,
		LOW_BITS,
		HIGH_BITS,
		BLANK_ADDRESS,

		NUM_TOKENS,

		//non-regex tokens
		EOT,
	};

	SSBCLang();
	~SSBCLang();
	int getTokenType(const string& str);

private:
	regex* expressions;

	void define(Token token, string regExp);
};

#define CASE_INTEGER \
	case SSBCLang::HEXADECIMAL:\
	case SSBCLang::DECIMAL:\
	case SSBCLang::OCTAL:\
	case SSBCLang::BINARY:

#endif