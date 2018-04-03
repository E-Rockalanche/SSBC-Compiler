#ifndef SSBC_HPP
#define SSBC_HPP

/*
SSBC
Simple Stack Based Computer
specs by Peter Walsh
written by Eric Roberts
*/

#include <fstream>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>
#include "../tool/Debug.hpp"
using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

class SSBC{
public:
	SSBC();
	void reset();
	void load(const char* filename);
	void run();
	void writeToPortB(char value);
	void writeToPortD(char value);
	char readFromPortA();
	char readFromPortC();

private:
	static const uint MEMORY_SIZE = 0x10000;
	static const uint PC_START = 0;
	static const uint SP_START = 0xfffa;
	static const uint PSW = 0xfffb;
	static const uint PORTA = 0xfffc;
	static const uint PORTB = 0xfffd;
	static const uint PORTC = 0xfffe;
	static const uint PORTD = 0xffff;
	static const uint Z_BIT = 7;
	static const uint N_BIT = 6;

	enum Operation{
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
		NUM_OPERATIONS
	};

	char memory[MEMORY_SIZE];
	#if(DEBUG)
		vector<string> comments;
	#endif
	uint stack_pointer;
	uint program_counter;
	bool fault_bit;
	bool halt_bit;
	bool break_bit;

	uint readAddress();
	void setPSW();
	string getAddressName(uint address);

	void noop();
	void halt();
	void pushimm();
	void pushext();
	void popinh();
	void popext();
	void jnz();
	void jnn();
	void jnbit(uint bit);
	void add();
	void sub();
	void nor();
	void fault(const char* message);
};

#endif