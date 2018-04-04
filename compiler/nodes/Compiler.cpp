#include "Compiler.hpp"
#include "StatementCompiler.hpp"

Compiler::Compiler(){
	index = 0;
	numLabels = 0;
	errors = 0;
	program = NULL;
	stdLibDir = "ssbclib/";
}

Compiler::~Compiler(){
	dout("Destroying compiler");

	if (program){
		delete program;
	}
}

void Compiler::addFile(string filename){
	inputFiles.push_back(filename);
}

void Compiler::setOutputFilename(string filename){
	if (outputFilename != ""){
		printWarning("Output file was already defined as " + outputFilename);
	}
	outputFilename = filename;
	asmFilename = filename + ".ssbc";
}

bool Compiler::parse(){
	dout("Compiler::parse()");

	if (program){
		dout("Deleting old program node");
		delete program;
		program = NULL;
	}

	program = new ProgramCompiler();
	if(program->parse()){
		return true;
	}else{
		delete program;
		program = NULL;
		return false;
	}
}

bool Compiler::compile(){
	errors = 0;
	assembly.clear();
	data.clear();
	numLabels = 0;
	outputComments = true;

	if (inputFiles.size() == 0){
		printError("No files given to compile");
		return false;
	}

	if (outputFilename == ""){
		printError("No output filename given");
		return false;
	}

	//later this will only show up at main() function
	writeAssembly(".start");

	for(unsigned int i = 0; i < inputFiles.size(); i++){
		compileFile(inputFiles[i]);
	}

	if (errors > 0){
		printError("Compilation failed. See errors above");
		return false;
	}

	writeToFile(asmFilename);

	assembler.addInputFile(asmFilename);
	assembler.addInputFile(stdLibDir + "math.ssbc");
	assembler.setOutputFilename(outputFilename);
	
	#if(DEBUG)
		assembler.setComments();
	#endif

	return assembler.assemble();
}

bool Compiler::compileFile(string filename){
	dout("Compiling " << filename);

	//clear data
	tokens.clear();
	scopeTable.clear();
	typeManager.clear();
	functionManager.clear();

	//tokenize
	Tokenizer tokenizer;
	tokenizer.setLang(new CppLang());
	tokenizer.tokenize(filename, &tokens);
	errors += tokenizer.errors();
	if (errors != 0){
		printError("Could not tokenize program");
		return false;
	}
	dout("Tokenization complete");

	//parse
	index = 0;
	if (!parse()){
		printError("Could not parse program");
		return false;
	}
	dout("Parse complete");

	//compile
	program->compile();
	dout("compilation complete");

	return (errors == 0);
}

bool Compiler::writeToFile(string filename){
	ofstream fout(filename);
	if (fout.fail()){
		printError("Cannot open file " + filename);
		return false;
	}
	for(unsigned int i = 0; i < assembly.size(); i++){
		fout << assembly[i] << '\n';
	}
	fout << "halt\n";
	for(unsigned int i = 0; i < data.size(); i++){
		fout << data[i] << '\n';
	}
	fout.close();
	return true;
}