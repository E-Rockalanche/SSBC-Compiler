#include "BaseCompiler.hpp"
#include "Type.hpp"
#include <stdexcept>
using namespace std;

//static variables

vector<string> BaseCompiler::assembly;
vector<string> BaseCompiler::globalData;

vector<Token> BaseCompiler::tokens;
unsigned int BaseCompiler::index;
unsigned int BaseCompiler::numLabels;
unsigned int BaseCompiler::errors;
bool BaseCompiler::outputComments;
unsigned int BaseCompiler::depth;

string BaseCompiler::functionReturnLabel;
string BaseCompiler::functionDataLabel;
Type BaseCompiler::functionReturnType;
bool BaseCompiler::inMain;

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
	assembly.push_back("\t" + str);
}

void BaseCompiler::writeGlobalData(string str){
	globalData.push_back(str);
}

void BaseCompiler::popToAddress(string label, unsigned int size){
	assert(label != "", "empty label in popToAddress");
	if (size > 0){

		const unsigned int sizeOfPopext = 3;
		if (size * sizeOfPopext <= 18){
			for(unsigned int i = 0; i < size; i++){
				writeAssembly("popext " + label + " + " + to_string(i));
			}
		}else{
			writeAssembly("pushimm16 " + label);
			writeAssembly("pushimm " + to_string(size));
			writeAssembly("jsr POP_TO_ADDR");
		}
	}
}

void BaseCompiler::pushFromAddress(string label, unsigned int size){
	assert(label != "", "empty label in pushFromAddress");
	if (size > 0){
	
		const unsigned int sizeOfPushext = 3;
		if (size * sizeOfPushext <= 18){
			for(int i = size-1; i >= 0; i--){
				writeAssembly("pushext " + label + " + " + to_string(i));
			}
		}else{
			writeAssembly("pushimm16 " + label);
			writeAssembly("pushimm " + to_string(size));
			writeAssembly("jsr PUSH_FROM_ADDR");
		}
	}
}

void BaseCompiler::writeComment(string comment){
	if (outputComments){
		assembly.push_back("/* " + comment + " */");
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

//class functions


BaseCompiler::~BaseCompiler(){}

bool BaseCompiler::parse(){
	ABSTRACT_CALL_ERROR
}
bool BaseCompiler::compile(){
	ABSTRACT_CALL_ERROR
}

