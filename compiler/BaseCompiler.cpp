#include "BaseCompiler.hpp"
#include "Type.hpp"
#include <stdexcept>
using namespace std;

//static variables

ScopeTable BaseCompiler::scopeTable;
TypeManager BaseCompiler::typeManager;
FunctionManager BaseCompiler::functionManager;
BreakManager BaseCompiler::breakManager;

vector<string> BaseCompiler::assembly;
vector<string> BaseCompiler::data;
vector<string> BaseCompiler::scopeData;

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

void BaseCompiler::writeData(string str){
	data.push_back(str);
}

void BaseCompiler::writeScopeData(string str){
	scopeData.push_back(str);
}

void BaseCompiler::appendScopeDataToAssembly(){
	dout("scopeData size = " << scopeData.size());
	for(unsigned int i = 0; i < scopeData.size(); i++){
		assembly.push_back(scopeData[i]);
	}
	scopeData.clear();
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

#define ABSTRACT_CALL_ERROR {throw runtime_error("Cannot call function of \
an abstract class");}

BaseCompiler::~BaseCompiler(){}

bool BaseCompiler::parse(){
	ABSTRACT_CALL_ERROR
}
bool BaseCompiler::compile(){
	ABSTRACT_CALL_ERROR
}

CompilerNode::~CompilerNode(){
	for(unsigned int i = 0; i < children.size(); i++){
		if(children[i]){
			delete children[i];
			children[i] = NULL;
		}
	}
}

bool CompilerNode::parse(){
	ABSTRACT_CALL_ERROR
}

bool CompilerNode::compile(){
	ABSTRACT_CALL_ERROR
}

int CompilerNode::getValue(){
	ABSTRACT_CALL_ERROR
}

bool CompilerNode::endsStatementSequence(){
	return endsSequence || returnsFromFunction();
}

bool CompilerNode::returnsFromFunction(){
	return returns;
}

Type CompilerNode::getType(){
	return type;
}

unsigned int CompilerNode::getIndex(){
	return startTokenIndex;
}