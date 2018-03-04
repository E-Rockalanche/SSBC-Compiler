#include <iostream>
#include <string>
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
  Q:  quit\n\
====================\n\n";

int main(){
	SSBC ssbc;
	char command;
	int port_value;
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
				cout << (int)ssbc.readFromPortA() << '\n';
			break;

			case 'b':
				cout << "Write to port B: ";
				cin >> port_value;
				ssbc.writeToPortB(port_value);
			break;

			case 'c':
				cout << "Port C: ";
				cout << (int)ssbc.readFromPortC() << '\n';
			break;

			case 'd':
				cout << "Write to port D: ";
				cin >> port_value;
				ssbc.writeToPortD(port_value);
			break;

			case 'q':
				cout << "Goodbye!\n";
			break;

			default:
				cout << "Invalid command\n";
		}
	}while(command != 'q');
}