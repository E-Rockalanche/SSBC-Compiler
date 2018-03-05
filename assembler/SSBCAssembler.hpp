#ifndef SSBCASSEMBLER_HPP
#define SSBCASSEMBLER_HPP

#include "LabelList.hpp"
#include "Tokenizer.hpp"
#include "SSBCLang.hpp"
#include "Debug.hpp"
#include "Assert.hpp" 
#include "Token.hpp"
#include "Binary.hpp"

class SSBCAssembler{
public:
	SSBCAssembler(int argc = 0, const char** argv = NULL);
	void assemble();
	void setWarnings(bool set = true);
	void setComments(bool set = true);
	void setOutputFilename(string filename);
	void addInputFile(string filename);

private:
	//assembly options
	bool warnings = false;
	bool outputComments = false;
	string outputFilename = "";

	LabelList labels;
	Tokenizer tokenizer;
	vector<string> inputFiles;
	vector<Token> tokens;
	
	unsigned int index;
	int errors;
	Binary binary;
	vector<string> comments;

	int numASMRegisters = 2;

	const static unsigned int MAX_BINARY_SIZE = 0xf000;
	const static unsigned int ASM = 0xfff9;
	const static unsigned int ASM2 = 0xfffa;
	const static unsigned int PSW = 0xfffb;
	const static unsigned int PORT_A = 0xfffc;
	const static unsigned int PORT_B = 0xfffd;
	const static unsigned int PORT_C = 0xfffe;
	const static unsigned int PORT_D = 0xffff;

	enum SSBCInstruction{
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
		NOR
	};

	Token endToken();
	void writeAddress(Token addressToken);
	void writeAscii(string str);

	//messages
	void error(string message);
	void warning(string message);
	void errorAt(string message);
	void warningAt(string message);
	void errorNear(string message);
	void warningNear(string message);

	//comments
	void writeComment(string comment);
	void writeComment(string comment, unsigned int address);
	string getComment(unsigned int i);

	void assembleFile(string filename);
	void statement();
	void writeToFile();

	Token nextToken();
	Token currentToken();

	unsigned int currentAddress();
	void checkForUndefinedReferences();

	//operands
	int getInteger();
	int parseInteger(Token token);
	int parseChar(Token charToken);
	int parseEscapeChar(char escapeChar);
	unsigned int getExt16Address();
	void pushimm16(unsigned int value);
	void identifier();
	void addressToken();
	void blankAddress();
	void labelDef();
	void defineLabelAsCurrentAddress(string label);
	void highLowAddress(bool high);
	void labelDefError(string label);
	void replaceLabelOccurrences(string label);
	void replaceLabelOccurrence(string label, unsigned int address,
		LabelList::Option option);

	//native instructions
	void noop();
	void halt();
	void pushimm();
	void pushext();
	void popinh();
	void popext();
	void jnz();
	void jnn();
	void add();
	void sub();
	void nor();

	//extended instructions
	void test();
	void pushimm16();
	void pushext16();
	void popinh16();
	void popext16();
	void jump();
	void jsr();
	void clear();
	void clearpsw();
	void clone();
	void bitwiseOr();
	void bitwiseAnd();
	void bitwiseNot();
	void nand();
	void compare();
	void inc();
	void dec();
	void swap();
	void move();
	void btest();
	void bset();
	void bclear();

	//directives
	void start();
	void global();
	void file();
	void byte();
	void word();
	void array();
	void ascii();
	void asciz();

	//literals
	void byteLiteral();

};

#endif