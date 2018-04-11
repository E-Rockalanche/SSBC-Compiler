#include <iostream>
#include <string>
#include <bitset>
#include "ssbc.hpp"
using namespace std;

const char* const MENU = "\n\
========= SSBC =========\n\
  l:  load\n\
  x:  execute\n\
\
  A:  read port A\n\
  B:  write port B\n\
  C:  read port C\n\
  D:  write port D\n\
\
  b:  add breakpoint\n\
  r:  remove breakpoint\n\
  c:  clear breakpoints\n\
  s:  step\n\
  m:  read memory\n\
  t:  display stack\n\
\
  q:  quit\n\
========================\n\n";

int main(){
	SSBC ssbc;
	char command;
	int port_value;
	int address;
	char value;
	string garbage;
	cout << MENU;
	do{
		cin >> command;
		string filename;
		switch(command){
			case 'l':
				cout << "File: ";
				cin >> filename;
				cout << "Loading\n";
				ssbc.load(filename.c_str());
				cout << "Finished\n";
			break;

			case 'x':
				cout << "Running\n";
				ssbc.run();
				cout << "Finished\n";
			break;

			case 'A':
				cout << "Port A: ";
				value = ssbc.readFromPortA();
				cout << bitset<8>(value) << " : " << (int)value << '\n';
			break;

			case 'B':
				cout << "Write to port B: ";
				cin >> port_value;
				ssbc.writeToPortB(port_value);
			break;

			case 'C':
				cout << "Port C: ";
				value = ssbc.readFromPortC();
				cout << bitset<8>(value) << " : " << (int)value << '\n';
			break;

			case 'D':
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

			case 'b':
				cout << "Add breakpoint: ";
				cin >> address;
				ssbc.setBreakPoint(address);
			break;

			case 'r':
				cout << "Remove breakpoint: ";
				cin >> address;
				ssbc.removeBreakPoint(address);
			break;

			case 'c':
				cout << "Cleared all breakpoints";
				ssbc.removeBreakPoints();
			break;

			case 's':
				ssbc.step();
			break;

			case 't':
				ssbc.displayStack();
			break;

			case 'h':
				cout << MENU;
			break;

			case 'q':
				cout << "Goodbye!\n";
			break;

			default:
				cout << "Invalid command\n";
				getline(cin, garbage);
		}
	}while(command != 'q');
}