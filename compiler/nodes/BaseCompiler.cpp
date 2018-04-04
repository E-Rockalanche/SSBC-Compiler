#include "BaseCompiler.hpp"
#include "Type.hpp"
#include <stdexcept>
using namespace std;

#define ABSTRACT_CALL_ERROR {throw runtime_error("Cannot call function of \
an abstract class");}

//static variables

ScopeTable BaseCompiler::scopeTable;
TypeManager BaseCompiler::typeManager;
FunctionManager BaseCompiler::functionManager;
vector<string> BaseCompiler::assembly;
vector<string> BaseCompiler::data;
vector<Token> BaseCompiler::tokens;
unsigned int BaseCompiler::index;
unsigned int BaseCompiler::numLabels;
unsigned int BaseCompiler::errors;
bool BaseCompiler::outputComments;
unsigned int BaseCompiler::depth;

//static functions

void BaseCompiler::incIndex(){
	++index;
}

Token BaseCompiler::nextToken(){
	Token token;
	do{
		if (++index < tokens.size()){
			token = tokens[index];
		}else{
			token = Token();
		}
	}while(token.type() == CppLang::COMMENT
		|| token.type() == CppLang::COMMENT_BLOCK);
	return token;
}

Token BaseCompiler::currentToken(){
	Token token;
	bool next = true;
	do{
		if (index < tokens.size()){
			token = tokens[index];
		}else{
			token = Token();
		}
		if (token.type() == CppLang::COMMENT
			|| token.type() == CppLang::COMMENT_BLOCK){
			index++;
		}else{
			next = false;
		}
	}while(next);
	return token;
}

void BaseCompiler::writeAssembly(string str){
	assembly.push_back(str);
}

void BaseCompiler::writeData(string str){
	data.push_back(str);
}

void BaseCompiler::writeComment(string comment){
	if (outputComments){
		assembly.push_back("/*\n" + comment + "\n*/");
	}
}

string BaseCompiler::newLabel(){
	return "L" + to_string(numLabels++);
}

void BaseCompiler::printError(string message){
	cout << "Error: " << message << '\n';
	errors++;
}

void BaseCompiler::printWarning(string message){
	cout << "Warning: " << message << '\n';
}

void BaseCompiler::printError(string message, unsigned int index){
	cout << "Error: " << message << " at " << getLocationString(index) << '\n';
	printRow(index);
	errors++;
}

void BaseCompiler::printWarning(string message, unsigned int index){
	cout << "Warning: " << message << " at " << getLocationString(index) << '\n';
	printRow(index);
}

string BaseCompiler::getLocationString(unsigned int index){
	assert(index < tokens.size(), "token index out of range");
	Token t = tokens[index];
	return "line " + to_string(t.row()) + ", column " + to_string(t.col());
}

void BaseCompiler::printRow(unsigned int index){
	int row = tokens[index].row();
	int col = tokens[index].col();
	int curRow = row;
	unsigned int curIndex = index;
	while(curIndex > 0){
		curIndex--;
		curRow = tokens[curIndex].row();
		if(curRow < row){
			curIndex++;
			break;
		}
	}
	int curCol = 1;
	Token t;
	do{
		t = tokens[curIndex];
		if (t.row() > row){
			break;
		}
		while(curCol < t.col()){
			cout << ' ';
			curCol++;
		}
		cout << t.value();
		curCol += t.value().size();
		curIndex++;
	}while((t.row() == row) && (curIndex < tokens.size()));
	cout << '\n';
	for(int i = 1; i < col; i++){
		cout << ' ';
	}
	cout << "^\n";
}

bool BaseCompiler::compileTypeConversion(const Type& from, const Type& to){
	if (!typeManager.canConvert(from, to)){
		printError("Cannot convert " + from.toString() + " to " + to.toString());
		return false;
	}

	unsigned int fromSize = typeManager.sizeOf(from);
	unsigned int toSize = typeManager.sizeOf(to);
	
	writeComment("Converting " + from.toString() + " to " + to.toString());

	if (to == Type("bool") && from != Type("bool")){
		string end = newLabel();
		string falseLabel = newLabel();
		switch(fromSize){
			case 1:
				//test if positive
				writeAssembly("popext ASM");
				writeAssembly("pushimm 0");
				writeAssembly("pushext ASM");
				writeAssembly("sub");
				writeAssembly("popinh");
				break;
			case 2:
				//test if positive
				writeAssembly("popext16 ASM2");
				writeAssembly("pushimm16 0");
				writeAssembly("pushext16 ASM2");
				writeAssembly("jsr SUB16");
				writeAssembly("jsr TEST16");
				writeAssembly("popext PSW");
				writeAssembly("popinh16");
				break;
			default:
				printError("Cannot convert " + from.toString() + " to bool");
				return false;
		}
		writeAssembly("jnn " + falseLabel);
		writeAssembly("pushimm 1");
		writeAssembly("jump " + end);
		writeAssembly(falseLabel + ": pushimm 0");
		writeAssembly(end + ":");
	}else{
		if (fromSize < toSize){
			if (fromSize == 0){
				printError("Cannot convert " + from.toString()
					+ " to " + to.toString());
				return false;
			}
			unsigned int diff = toSize - fromSize;
			//maintain sign
			writeAssembly("test");
			string posLabel = newLabel();
			string endLabel = newLabel();
			writeAssembly("jnn " + posLabel);
			for(unsigned int i = 0; i < diff; i++){
				writeAssembly("pushimm 0xff");
			}
			writeAssembly("jump " + endLabel);
			writeAssembly(posLabel + ":");
			for(unsigned int i = 0; i < diff; i++){
				writeAssembly("pushimm 0");
			}
			writeAssembly(endLabel + ":");
		}

		for(unsigned int i = toSize; i < fromSize; i++){
			writeAssembly("popinh");
		}
	}
	writeComment("End type conversion");
	return true;
}

//class functions

BaseCompiler::~BaseCompiler(){}
bool BaseCompiler::parse(){
	ABSTRACT_CALL_ERROR
}
bool BaseCompiler::compile(){
	ABSTRACT_CALL_ERROR
}

CompilerNode::~CompilerNode(){
	for(unsigned int i = 0; i < children.size(); i++){
		delete children[i];
	}
}
bool CompilerNode::parse(){
	ABSTRACT_CALL_ERROR
}
bool CompilerNode::compile(){
	ABSTRACT_CALL_ERROR
}
Type CompilerNode::getType(){
	return type;
}
unsigned int CompilerNode::getIndex(){
	return startTokenIndex;
}