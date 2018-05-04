#ifndef BASE_COMPILER_HPP
#define BASE_COMPILER_HPP

#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>

#include "Type.hpp"
#include "CppLang.hpp"
#include "CompilerDebug.hpp"
#include "Assert.hpp"
#include "Token.hpp"

//helper objects
#include "ScopeTable.hpp"
#include "TypeManager.hpp"
#include "FunctionManager.hpp"
#include "BreakManager.hpp"

using namespace std;

//begin parsing a grammar rule
//use to remember the starting index of the current rule
#if (DEBUG)
	#define P_BEGIN {startTokenIndex = index; INC_DEPTH DEPTH_SPACES \
		cout << "Parsing " << __FILE__ << " on " << currentToken().value() \
		<< '\n';}
#else
	#define P_BEGIN {startTokenIndex = index;}
#endif

//add a compiler node. End parse if successful, continue otherwise
#define P_TRY_NODE(N) {CompilerNode* node = (N); if (node->parse())\
	{children.push_back(node); P_END} else {delete node;}}

//add a compiler node. Fail if it does not parse
#define P_ADD_NODE(N) {CompilerNode* node = (N); if (node->parse())\
	{children.push_back(node);} else {delete node; P_FAIL}}

//add a compiler node if it parses
#define P_OPTIONAL_NODE(N) {CompilerNode* node = (N); if (node->parse())\
	{children.push_back(node);} else {delete node;}}

//add a compiler node if it parses
#define P_OPTIONAL_NODE_SET(N, S) {CompilerNode* node = (N); if (node->parse())\
	{children.push_back(node); S} else {delete node;}}

//add multiple compiler nodes until a parse fails
#define P_LOOP_NODE(N) {bool ok = true; while(ok){CompilerNode* node = (N);\
	if (node->parse()){children.push_back(node);} else {delete node;\
	ok = false;}if(index >= tokens.size()){ok = false;}}}

#define P_EXPECT_TOKEN(T) {if (currentToken().type() == (T)){incIndex();}\
	else P_FAIL}

#define P_EXPECT_TOKEN_SET(T, BEFORE, AFTER) {if (currentToken().type() == (T))\
	{BEFORE; incIndex(); AFTER;} else P_FAIL}

#define P_OPTIONAL_TOKEN(T) {if (currentToken().type() == (T){incIndex();})}

#define P_OPTIONAL_TOKEN_SET(T, BEFORE, AFTER) {if (currentToken().type() == (T))\
	{BEFORE; incIndex(); AFTER;}}

//current parse is successful
#if (DEBUG)
	#define P_END {DEPTH_SPACES DEC_DEPTH cout << "Successful parse in "\
		<< __FILE__ << '\n'; return true;}
#else
	#define P_END {return true;}
#endif

#define ASSERT_TYPES {for(unsigned int i = 0; i < children.size(); i++)\
	{Type t = children[i]->getType(); if (!t.isDefined()){return false;}\
	if (t == Type("void")){printError("void type", children[i]->getIndex());\
	return false;}}}

//use to fail the current rule parse. Sets the global token index back to the
//current rule's starting index
#if (DEBUG)
	#define P_FAIL {DEPTH_SPACES DEC_DEPTH cout << "Failed parse in " << __FILE__ << " on token \""\
		<< currentToken().value() << "\" at (" << currentToken().row() << ", "\
		<< currentToken().col() << ")\n"; index = startTokenIndex;\
		return false;}
#else
	#define P_FAIL {index = startTokenIndex; return false;}
#endif

#define INC_DEPTH {depth++;}
#define DEC_DEPTH {depth--;}
#define DEPTH_SPACES {for(unsigned int i = 0; i < depth; i++){cout << "  ";}}

class BaseCompiler {
public:
	virtual ~BaseCompiler() = 0;
	virtual bool parse() = 0;
	virtual bool compile() = 0;

protected:
	static void incIndex();
	static Token nextToken();
	static Token currentToken();

	static void writeAssembly(string str);
	static void writeGlobalData(string str);
	static void popToAddress(string label, unsigned int size);
	static void pushFromAddress(string label, unsigned int size);
	static void popToAddress(unsigned int size);
	static void pushFromAddress(unsigned int size);

	static void writeComment(string comment);
	static string newLabel();
	static void printError(string message);
	static void printWarning(string message);
	static void printError(string message, unsigned int index);
	static void printWarning(string message, unsigned int index);
	static string getLocationString(unsigned int index);
	static void printRow(unsigned int index);

	//helper objects
	static ScopeTable scopeTable;
	static TypeManager typeManager;
	static FunctionManager functionManager;
	static BreakManager breakManager;

	//file specific
	static vector<Token> tokens;
	static unsigned int index;
	static unsigned int depth;//debug purposes
	
	//current function info
	static string functionReturnLabel;
	static string functionDataLabel;
	static Type functionReturnType;
	static bool inMain;

	static vector<string> assembly;
	static vector<string> globalData;

	static unsigned int numLabels;
	static unsigned int errors;
	static bool outputComments;
};

#endif