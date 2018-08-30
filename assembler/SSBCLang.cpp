#include "SSBCLang.hpp"
#include <string>
using namespace std;

SSBCLang::SSBCLang(){
	expressions = new regex[NUM_TOKENS];
	
	//native instructions
	define(NOOP, "noop");
	define(HALT, "halt");
	define(PUSHIMM, "pushimm");
	define(PUSHEXT, "pushext");
	define(POPINH, "popinh");
	define(POPEXT, "popext");
	define(JNZ, "jnz");
	define(JNN, "jnn");
	define(ADD, "add");
	define(SUB, "sub");
	define(NOR, "nor");

	//extended instructions
	define(TEST, "test");
	define(PUSHIMM16, "pushimm16");
	define(PUSHEXT16, "pushext16");
	define(POPINH16, "popinh16");
	define(POPEXT16, "popext16");
	define(JUMP, "jump");
	define(JSR, "jsr");
	define(CLEAR, "clear");
	define(CLEARPSW, "clearpsw");
	define(CLONE, "clone");
	define(OR, "or");
	define(AND, "and");
	define(NOT, "not");
	define(NAND, "nand");
	define(COMPARE, "compare");
	define(INC, "inc");
	define(DEC, "dec");
	define(SWAP, "swap");
	define(MOVE, "move");
	define(BTEST, "btest");
	define(BSET, "bset");
	define(BCLEAR, "bclear");

	//directives
	define(START, "\\.start");
	define(GLOBAL, "\\.global");
	define(FILE, "\\.file");
	define(INCLUDE, "\\.include");
	define(BYTE, "\\.byte");
	define(WORD, "\\.word");
	define(ARRAY, "\\.array");
	define(ASCII, "\\.ascii");
	define(ASCIZ, "\\.asciz");

	//literals
	define(HEXADECIMAL, "0x[0-9a-fA-F]*");
	define(DECIMAL, "[-+]?[1-9][0-9]*");
	define(OCTAL, "0[0-7]*");
	define(BINARY, "0b[01]*");
	define(CHAR,   "'([^\\\\']|(\\\\.))'");
	define(STRING, "\"([^\\\\\"]|(\\\\.))*\"");

	//other
	define(PLUS, "\\+");
	define(COMMENT, "//[ -~\\t]*(\\n)?");
	define(COMMENT_BLOCK, "/\\*[ -~\\t\\n\\r\\f]*\\*/");
	define(IDENTIFIER, "[a-zA-Z_\\.]+[a-zA-Z0-9_]*");
	define(COLON, ":");
	define(LOW_BITS, ">");
	define(HIGH_BITS, "<");
	define(BLANK_ADDRESS, "\\?");
}

SSBCLang::~SSBCLang(){
	delete[] expressions;
}

int SSBCLang::getTokenType(const string& str){
	for(unsigned int i = 0; i < NUM_TOKENS; i++){
		if (regex_match(str, expressions[i])){
			return i;
		}
	}
	return INVALID_TOKEN;
}

void SSBCLang::define(Token token, string regExp){
	expressions[token] = regex("^" + regExp + "$");
}
