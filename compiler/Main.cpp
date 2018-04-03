#include "Compiler.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char** argv){
	Compiler compiler;
	for(int i = 1; i < argc; i++){
		if (argv[i] == string("-o")){
			i++;
			if (i < argc){
				compiler.setOutputFilename(argv[i]);
			}else{
				cout << "Error: Output filename flag given but no filename\n";
			}
		}else{
			compiler.addFile(argv[i]);
		}
	}
	compiler.compile();

	return 0;
}