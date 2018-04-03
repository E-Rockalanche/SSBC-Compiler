#ifndef COMPILER_HPP
#define COMPILER_HPP

#include "BaseCompiler.hpp"
#include "SSBCAssembler.hpp"

class Compiler : public CompilerNode {
public:
	Compiler();
	~Compiler();
	void addFile(string filename);
	void setOutputFilename(string filename);
	bool compile();

private:
	bool parse();
	SSBCAssembler assembler;
	vector<string> inputFiles;
	string asmFilename;
	string outputFilename;
	bool createAsm;

	bool compileFile(string filename);
	bool writeToFile(string filename);
};

#endif