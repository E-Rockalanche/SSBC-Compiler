#include "Binary.hpp"

void Binary::write8bit(int num){
	num = num % 256;
	binary.push_back(bitset<8>(num));
}

void Binary::write8bit(int num, unsigned int address){
	num = num % 256;
	if (address >= binary.size()){
		bitset<8> zero(0);
		binary.resize(address+1, zero);
	}
	binary[address] = bitset<8>(num);
}

void Binary::write16bit(int num){
	write8bit((num >> 8) & 255);//high bits
	write8bit(num & 255);//low bits
}

void Binary::write16bit(int num, unsigned int address){
	write8bit(num & 255, address + 1);//low bits
	write8bit((num >> 8) & 255, address);//high bits
}