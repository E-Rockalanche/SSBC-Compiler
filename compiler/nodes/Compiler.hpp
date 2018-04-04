#ifndef COMPILER_HPP
#define COMPILER_HPP

#include "BaseCompiler.hpp"
#include "SSBCAssembler.hpp"
#include "ProgramCompiler.hpp"

class Compiler : public BaseCompiler {
public:
	Compiler();
	~Compiler();
	void addFile(string filename);
	void setOutputFilename(string filename);
	bool compile();

private:
	SSBCAssembler assembler;
	vector<string> inputFiles;
	string asmFilename;
	string outputFilename;
	bool createAsm;
	ProgramCompiler* program;
	string stdLibDir;

	bool parse();
	bool compileFile(string filename);
	bool writeToFile(string filename);
};

#endif