#ifndef BINARY_HPP
#define BINARY_HPP

#include <vector>
#include <bitset>
using namespace std;

class Binary{
public:
	void write8bit(int num);
	void write8bit(int num, unsigned int address);
	void write16bit(int num);
	void write16bit(int num, unsigned int address);
	unsigned int size(){return binary.size();}
	bitset<8> operator[](unsigned int address){return binary[address];}

private:
	vector<bitset<8>> binary;
};

#endif