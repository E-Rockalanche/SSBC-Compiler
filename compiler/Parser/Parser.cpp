#include "Parser.hpp"
#include "Debug.hpp"

void Parser::setTokens(vector<Token>* tokens){
	
	if (tokens == NULL){
		cout << "Error: NULL token vector given in Parser::setTokens()\n";
	}else{
		this->tokens = tokens;
	}
}

Token Parser::endToken(){
	return Token(EOT, "EOT", tokens->back().row(), tokens->back().col());
}

Token Parser::currentToken(){
	if (index < tokens->size()){
		Token t = tokens->at(index);
		if (t.type() != CppLang::COMMENT && t.type() != CppLang::COMMENT_BLOCK){
			return tokens->at(index);
		}else{
			index++;
			return currentToken();
		}
	}
	return endToken();
}

Token Parser::nextToken(){
	++index;
	return currentToken();
}

void Parser::errorAt(const string& str){
	Token t = currentToken();
	cout << "Error: " << str << " at (" << t.col() << "," << t.row() << ")\n";
	errors++;
}

void Parser::error(const string& str){
	cout << "Error: " << str << '\n';
	errors++;
}

//start of parse function
//remembers the index at invokation
//create the parent node
#define P_BEGIN(parent_type) unsigned int _start_ = index;\
	Branch* parent = new Branch(parent_type);\
	{INC_DEPTH DEPTH_SPACES cout << "Begin " << __FUNCTION__ << ": " <<\
	currentToken().value() << '\n';}
//expect the same parse 0-many times
//add each parse to the parent
//when a parse fails, index is set to the end of the last parse
#define P_LOOP(N) {unsigned int _loopStart_; Tree* _loopNode_;\
	while(true){_loopStart_ = index; _loopNode_ = (N); if (_loopNode_){\
	P_ADDCHILD(_loopNode_) _start_ = index;} else {\
	index = _loopStart_; break;}}}
//expect but skip over token N
#define P_SKIP_TOKEN(N) {if (currentToken().type() != (N)) P_FAIL \
	else index++;}
//try parse N, if it works, return
#define P_TRY(N) {Tree* _node_ = (N); if (_node_) {parent->addChild(_node_);\
	P_END}}

//try to deprecate this

//check if parse N works
//if so add the returned node to the parent
#define P_OPTIONAL_NODE(N) {Tree* _node_ = (N); if (_node_) \
	parent->addChild(_node_);}
//check if the current token is equal to N
//if so , add it to the parent and go to the next token
#define P_OPTIONAL_TOKEN(N) {if (currentToken().type() == (N))\
	{parent->addChild(new Leaf(index++));}}


//tries to add the given node to the current parent
//if the given node is NULL, the parent is destroyed and
//the current function returns NULL
#define P_ADDCHILD(N) {Tree* _node_ = N; P_ASSERT(_node_) \
	parent->addChild(_node_);}
//expect a token of type N and add it to the parent
//return NULL and destroy parent if the next current token is not N
#define P_EXPECT_TOKEN(N) {P_ASSERT(currentToken().type() == (N)) \
	parent->addChild(new Leaf(index++));}
//destroys the current parent and returns NULL if the assert does not pass
#define P_ASSERT(N) {if (!(N)) P_FAIL}
//fails the current parse rule
//sets the index to the value at invokation and returns a bad node
#define P_FAIL {DEPTH_SPACES DEC_DEPTH\
	cout << "Fail in " << __FUNCTION__ << " on token: " <<\
	currentToken().value() << '\n';\
	index = _start_; if (parent){delete parent;} return NULL;}
//parse is successful. return the parent node
#define P_END {DEPTH_SPACES cout << "Success in " << __FUNCTION__ << '\n';\
	DEC_DEPTH return parent;}

#define DEPTH_SPACES for(unsigned int i = 0; i < _global_parse_tree_depth_; i++)\
	{cout << "  ";}

#if(DEBUG)
	unsigned int _global_parse_tree_depth_ = 0;
	#define INC_DEPTH {++_global_parse_tree_depth_;}
	#define DEC_DEPTH {--_global_parse_tree_depth_;}
#else
	#define INC_DEPTH
	#define DEC_DEPTH
#endif

Tree* Parser::parse(){
	assert(tokens != NULL, "tokens is NULL");
	index = 0;

	P_BEGIN(PROGRAM)
	P_LOOP(parseGlobalStatement())

	if (index < tokens->size()){
		errorAt("Could not parse statement starting");
		P_FAIL
	}

	P_END
}

Tree* Parser::parseGlobalStatement(){
	P_BEGIN(G_STATEMENT)
	P_TRY(parseFunctionDef())
	P_TRY(parseGlobalVarDef())
	P_FAIL
}

Tree* Parser::parseStatement(){
	P_BEGIN(STATEMENT)
	P_TRY(parseCodeBlock())
	P_TRY(parseDefAssignment())
	P_TRY(parseAssignment())
	P_TRY(parseFunctionCall())
	P_TRY(parseReturnStatement())
	P_TRY(parseForLoop())
	P_TRY(parseWhileLoop())
	P_TRY(parseDoWhileLoop())
	P_TRY(parseIfElse())
	P_TRY(parseSwitch())
	P_TRY(parseBreakStatement())
	P_TRY(parseContinueStatement())
	P_FAIL
}

Tree* Parser::parseGlobalVarDef(){
	P_BEGIN(G_VARDEF)
	P_ADDCHILD(parseDataType())
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_SKIP_TOKEN(CppLang::ASSIGN)
	P_ADDCHILD(parseLiteral())
	P_END
}

Tree* Parser::parseDataType(){
	P_BEGIN(DATATYPE)
	P_OPTIONAL_TOKEN(CppLang::CONST)
	switch(currentToken().type()){
		CASE_PRIMITIVE
		case CppLang::IDENTIFIER:
			P_EXPECT_TOKEN(currentToken().type())
			break;
		default:
			P_FAIL
	}
	P_ADDCHILD(parsePointers())
	P_END
}

Tree* Parser::parsePointers(){
	P_BEGIN(POINTERS)
	Tree* pointer = parsePointer();
	if (pointer){
		P_ADDCHILD(pointer)
		P_ADDCHILD(parsePointers())
	}
	P_END
}

Tree* Parser::parsePointer(){
	P_BEGIN(POINTER)
	P_EXPECT_TOKEN(CppLang::ASTERISK)
	P_OPTIONAL_TOKEN(CppLang::CONST)
	P_END
}

Tree* Parser::parseLiteral(){
	P_BEGIN(LITERAL)
	switch(currentToken().type()){
		CASE_LITERAL
			P_EXPECT_TOKEN(currentToken().type())
			break;
		default:
			P_FAIL
	}
	P_END
}

Tree* Parser::parseFunctionDef(){
	P_BEGIN(FUNCTION_DEF)
	P_ADDCHILD(parseDataType())
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_ADDCHILD(parseParameterList())
	P_ADDCHILD(parseCodeBlock())
	P_END
}

Tree* Parser::parseCodeBlock(){
	P_BEGIN(CODE_BLOCK)
	P_SKIP_TOKEN(CppLang::OPEN_BRACE)
	P_LOOP(parseStatement())
	P_SKIP_TOKEN(CppLang::CLOSE_BRACE)
	P_END
}

Tree* Parser::parseDefAssignment(){
	P_BEGIN(DEF_ASSIGNMENT)
	P_ADDCHILD(parseDataType())
	P_ADDCHILD(parseAssignment())
	P_END
}

Tree* Parser::parseAssignment(){
	P_BEGIN(ASSIGNMENT)
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_ADDCHILD(parseAssignOp())
	P_ADDCHILD(parseExpression())
	P_END
}

Tree* Parser::parseAssignOp(){
	P_BEGIN(ASSIGN_OP)
	switch(currentToken().type()){
		case CppLang::ASSIGN:
			P_EXPECT_TOKEN(currentToken().type())
			break;
		default:
			P_FAIL
	}
	P_END
}

Tree* Parser::parseExpression(){
	P_BEGIN(BOOL_EXP)
	P_ADDCHILD(parseRelationalExpression())
	switch(currentToken().type()){
		case CppLang::OR:
		case CppLang::AND:
			P_EXPECT_TOKEN(currentToken().type())
			P_ADDCHILD(parseExpression())
		default:
			P_END
	}
}

Tree* Parser::parseRelationalExpression(){
	P_BEGIN(RELATIONAL_EXP)
	P_ADDCHILD(parseEqualityExpression())
	switch(currentToken().type()){
		case CppLang::GREATER:
		case CppLang::LESSER:
		case CppLang::GREATER_EQUALS:
		case CppLang::LESSER_EQUALS:
			P_EXPECT_TOKEN(currentToken().type())
			P_ADDCHILD(parseRelationalExpression())
		default:
			P_END
	}
}

Tree* Parser::parseEqualityExpression(){
	P_BEGIN(EQUALITY_EXP)
	P_ADDCHILD(parseBitwiseExpression())
	switch(currentToken().type()){
		case CppLang::EQUALS:
		case CppLang::NOT_EQUALS:
			P_EXPECT_TOKEN(currentToken().type())
			P_ADDCHILD(parseEqualityExpression())
		default:
			P_END
	}
}

Tree* Parser::parseBitwiseExpression(){
	P_BEGIN(BITWISE_EXP)
	P_ADDCHILD(parseBitShiftExpression())
	switch(currentToken().type()){
		case CppLang::AMPERSAND:
		case CppLang::BIT_OR:
		case CppLang::BIT_XOR:
			P_EXPECT_TOKEN(currentToken().type())
			P_ADDCHILD(parseBitwiseExpression())
		default:
			P_END
	}
}

Tree* Parser::parseBitShiftExpression(){
	P_BEGIN(BITSHIFT_EXP)
	P_ADDCHILD(parseAdditiveExpression())
	switch(currentToken().type()){
		case CppLang::SHIFT_LEFT:
		case CppLang::SHIFT_RIGHT:
			P_EXPECT_TOKEN(currentToken().type())
			P_ADDCHILD(parseBitShiftExpression())
		default:
			P_END
	}
}

Tree* Parser::parseAdditiveExpression(){
	P_BEGIN(ADDITIVE_EXP)
	P_ADDCHILD(parseMultiplicitiveExpression())
	switch(currentToken().type()){
		case CppLang::ADD:
		case CppLang::SUB:
			P_EXPECT_TOKEN(currentToken().type())
			P_ADDCHILD(parseAdditiveExpression())
		default:
			P_END
	}
}

Tree* Parser::parseMultiplicitiveExpression(){
	P_BEGIN(MULTIPLICITIVE_EXP)
	P_ADDCHILD(parseUnaryExpression())
	switch(currentToken().type()){
		case CppLang::ASTERISK:
		case CppLang::DIV:
		case CppLang::MOD:
			P_EXPECT_TOKEN(currentToken().type())
			P_ADDCHILD(parseMultiplicitiveExpression())
		default:
			P_END
	}
}

Tree* Parser::parseUnaryExpression(){
	P_BEGIN(UNARY_EXP)
	P_TRY(parseBitNot())
	P_TRY(parseBoolNot())
	P_TRY(parseDereference())
	P_TRY(parseIncrement())
	P_TRY(parseDecrement())
	P_TRY(parsePostIncrement())
	P_TRY(parsePostDecrement())
	P_TRY(parseEnclosedExpression())
	P_TRY(parseLiteral())
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_END
}

Tree* Parser::parseEnclosedExpression(){
	P_BEGIN(ENCLOSED_EXPRESSION)
	P_SKIP_TOKEN(CppLang::OPEN_PAREN)
	P_ADDCHILD(parseExpression())
	P_SKIP_TOKEN(CppLang::CLOSE_PAREN)
	P_END
}

Tree* Parser::parseBitNot(){
	P_BEGIN(BIT_NOT)
	P_SKIP_TOKEN(CppLang::TILDE)
	P_ADDCHILD(parseUnaryExpression())
	P_END
}

Tree* Parser::parseBoolNot(){
	P_BEGIN(BOOL_NOT)
	P_SKIP_TOKEN(CppLang::NOT)
	P_ADDCHILD(parseUnaryExpression())
	P_END
}

Tree* Parser::parseDereference(){
	P_BEGIN(BOOL_NOT)
	P_SKIP_TOKEN(CppLang::ASTERISK)
	P_ADDCHILD(parseUnaryExpression())
	P_END
}

Tree* Parser::parseIncrement(){
	P_BEGIN(INCREMENT)
	P_SKIP_TOKEN(CppLang::INC)
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_END
}

Tree* Parser::parseDecrement(){
	P_BEGIN(DECREMENT)
	P_SKIP_TOKEN(CppLang::DEC)
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_END
}

Tree* Parser::parsePostIncrement(){
	P_BEGIN(POST_INCREMENT)
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_SKIP_TOKEN(CppLang::INC)
	P_END
}

Tree* Parser::parsePostDecrement(){
	P_BEGIN(POST_DECREMENT)
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_SKIP_TOKEN(CppLang::DEC)
	P_END
}

Tree* Parser::parseArrayAccessor(){
	P_BEGIN(ARRAY_ACCESSOR)
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_SKIP_TOKEN(CppLang::OPEN_BRACKET)
	P_ADDCHILD(parseExpression())
	P_SKIP_TOKEN(CppLang::CLOSE_BRACKET)
	P_END
}

Tree* Parser::parseParameterList(){
	P_BEGIN(PARAMETER_LIST)
	P_SKIP_TOKEN(CppLang::OPEN_PAREN)
	P_OPTIONAL_NODE(parseParameters())
	P_SKIP_TOKEN(CppLang::CLOSE_PAREN)
	P_END
}

Tree* Parser::parseParameters(){
	P_BEGIN(PARAMETERS)
	P_ADDCHILD(parseParameter())
	if (currentToken().type() == CppLang::COMMA){
		P_SKIP_TOKEN(CppLang::COMMA)
		P_ADDCHILD(parseParameters())
	}
	P_END
}

Tree* Parser::parseParameter(){
	P_BEGIN(PARAMETER)
	P_ADDCHILD(parseDataType())
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_END
}

Tree* Parser::parseReturnStatement(){
	P_BEGIN(RETURN_STATEMENT)
	P_SKIP_TOKEN(CppLang::RETURN)
	P_OPTIONAL_NODE(parseExpression())
	P_END
}

Tree* Parser::parseFunctionCall(){
	P_BEGIN(FUNCTION_CALL)
	P_EXPECT_TOKEN(CppLang::IDENTIFIER)
	P_SKIP_TOKEN(CppLang::OPEN_PAREN)
	P_ADDCHILD(parseArguments())
	P_SKIP_TOKEN(CppLang::CLOSE_PAREN)
	P_END
}

Tree* Parser::parseArguments(){
	P_BEGIN(ARGUMENTS)
	P_ADDCHILD(parseArgument())
	if (currentToken().type() == CppLang::COMMA){
		P_SKIP_TOKEN(CppLang::COMMA)
		P_ADDCHILD(parseArguments())
	}
	P_END
}

Tree* Parser::parseArgument(){
	P_BEGIN(ARGUMENT)
	P_OPTIONAL_NODE(parseExpression())
	P_END
}

Tree* Parser::parseWhileLoop(){
	P_BEGIN(WHILE_LOOP)
	P_SKIP_TOKEN(CppLang::WHILE)
	P_SKIP_TOKEN(CppLang::OPEN_PAREN)
	P_ADDCHILD(parseExpression())
	P_SKIP_TOKEN(CppLang::CLOSE_PAREN)
	P_ADDCHILD(parseStatement())
	P_END
}

Tree* Parser::parseDoWhileLoop(){
	P_BEGIN(DOWHILE_LOOP)
	P_SKIP_TOKEN(CppLang::DO)
	P_ADDCHILD(parseStatement())
	P_SKIP_TOKEN(CppLang::WHILE)
	P_SKIP_TOKEN(CppLang::OPEN_PAREN)
	P_ADDCHILD(parseExpression())
	P_SKIP_TOKEN(CppLang::CLOSE_PAREN)
	P_END
}

Tree* Parser::parseForLoop(){
	P_BEGIN(FOR_LOOP)
	P_SKIP_TOKEN(CppLang::FOR)
	P_SKIP_TOKEN(CppLang::OPEN_PAREN)
	P_OPTIONAL_NODE(parseStatement())
	P_SKIP_TOKEN(CppLang::SEMICOLON)
	P_OPTIONAL_NODE(parseExpression())
	P_SKIP_TOKEN(CppLang::SEMICOLON)
	P_OPTIONAL_NODE(parseStatement())
	P_SKIP_TOKEN(CppLang::CLOSE_PAREN)
	P_ADDCHILD(parseStatement())
	P_END
}

Tree* Parser::parseIfElse(){
	P_BEGIN(IF_ELSE)
	P_SKIP_TOKEN(CppLang::IF)
	P_SKIP_TOKEN(CppLang::OPEN_PAREN)
	P_ADDCHILD(parseExpression())
	P_SKIP_TOKEN(CppLang::CLOSE_PAREN)
	P_ADDCHILD(parseStatement())
	if (currentToken().type() == CppLang::ELSE){
		P_SKIP_TOKEN(CppLang::ELSE)
		P_ADDCHILD(parseStatement())
	}
	P_END
}

Tree* Parser::parseSwitch(){
	P_BEGIN(SWITCH)
	P_SKIP_TOKEN(CppLang::SWITCH)
	P_SKIP_TOKEN(CppLang::OPEN_PAREN)
	P_ADDCHILD(parseExpression())
	P_SKIP_TOKEN(CppLang::CLOSE_PAREN)
	P_SKIP_TOKEN(CppLang::OPEN_BRACE)
	P_LOOP(parseSwitchCase())
	P_SKIP_TOKEN(CppLang::CLOSE_BRACE)
	P_END
}

Tree* Parser::parseSwitchCase(){
	P_BEGIN(SWITCH_CASE)
	P_ADDCHILD(parseCase())
	P_LOOP(parseStatement())
	P_END
}

Tree* Parser::parseCase(){
	P_BEGIN(CASE)
	switch(currentToken().type()){
		case CppLang::DEFAULT:
			P_EXPECT_TOKEN(CppLang::DEFAULT)
			P_SKIP_TOKEN(CppLang::COLON)
			break;
		case CppLang::CASE:
			P_SKIP_TOKEN(CppLang::CASE)
			P_ADDCHILD(parseLiteral())
			P_SKIP_TOKEN(CppLang::COLON)
			break;
		default:
			P_FAIL
	}
	P_END
}

Tree* Parser::parseBreakStatement(){
	P_BEGIN(BREAK_STATEMENT)
	P_SKIP_TOKEN(CppLang::BREAK)
	P_END
}

Tree* Parser::parseContinueStatement(){
	P_BEGIN(CONTINUE_STATEMENT)
	P_SKIP_TOKEN(CppLang::CONTINUE)
	P_END
}