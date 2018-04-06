#include <iostream>
#include <string>
#include <bitset>
#include "ssbc.hpp"
using namespace std;

const char* MENU = "\n\
====================\n\
  L:  load\n\
  R:  run\n\
  A:  read port A\n\
  B:  write port B\n\
  C:  read port C\n\
  D:  write port D\n\
  M:  read memory\n\
  S:  display stack\n\
  Q:  quit\n\
====================\n\n";

int main(){
	SSBC ssbc;
	char command;
	int port_value;
	int address;
	char value;
	do{
		cout << MENU;
		cin >> command;
		string filename;
		switch(command){
			case 'l':
				cout << "Load file: ";
				cin >> filename;
				ssbc.load(filename.c_str());
			break;

			case 'r':
				cout << "Running\n";
				ssbc.run();
			break;

			case 'a':
				cout << "Port A: ";
				value = ssbc.readFromPortA();
				cout << bitset<8>(value) << " : " << (int)value << '\n';
			break;

			case 'b':
				cout << "Write to port B: ";
				cin >> port_value;
				ssbc.writeToPortB(port_value);
			break;

			case 'c':
				cout << "Port C: ";
				value = ssbc.readFromPortC();
				cout << bitset<8>(value) << " : " << (int)value << '\n';
			break;

			case 'd':
				cout << "Write to port D: ";
				cin >> port_value;
				ssbc.writeToPortD(port_value);
			break;

			case 'm':
				cout << "Address: ";
				cin >> address;
				value = ssbc.readFromMemory(address);
				cout << bitset<8>(value) << " : " << (int)value << '\n';
			break;

			case 's':
				ssbc.displayStack();
			break;

			case 'q':
				cout << "Goodbye!\n";
			break;

			default:
				cout << "Invalid command\n";
		}
	}while(command != 'q');
}