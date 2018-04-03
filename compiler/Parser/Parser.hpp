#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <exception>
#include "Token.hpp"
#include "ParseTree.hpp"
#include "CppLang.hpp"
#include "Assert.hpp"
using namespace std;

class Parser{
public:
	enum GrammarRule{
		PROGRAM,	//-> [G_STATEMENT]
		G_STATEMENT,	//-> FUNCTION_DEF
						//-> G_VARDEF
		G_VARDEF,	//-> DATATYPE IDENTIFIER
					//-> DATATYPE IDENTIFIER = LITERAL
		DATATYPE,	//-> const IDENTIFIER POINTERS
					//-> IDENTIFIER POINTERS
		POINTERS,	//-> POINTER POINTERS
					//->
		POINTER,	//-> * const
					//-> *
		FUNCTION_DEF,	//-> DATATYPE IDENTIFIER PARAM_LIST CODE_BLOCK
		PARAMETER_LIST,	//-> ( PARAMETERS )
						//-> ( )
		PARAMETERS,	//-> PARAMETER , PARAMETERS
					//-> PARAMETER
		PARAMETER,	//-> DATATYPE IDENTIFIER
		CODE_BLOCK,	//-> { [STATEMENT] }
		STATEMENT,	//-> DEF_ASSIGNMENT
						//-> ASSIGNMENT
						//-> FUNCTION_CALL
						//-> RETURN
						//-> CODE_BLOCK
		DEF_ASSIGNMENT,	//-> DATATYPE ASSIGNMENT
		ASSIGNMENT,		//-> IDENTIFIER = EXPRESSION
		FUNCTION_CALL,	//-> identifier ( ARGUMENTS )
		ARGUMENTS,	//-> ARGUMENT , ARGUMENTS
					//-> ARGUMENT
		ARGUMENT,	//-> EXPRESSION
					//-> e
		RETURN_STATEMENT,	//-> return EXPRESSION
		//EXPRESSION, //-> BOOL_EXP
		BOOL_EXP,	//-> REL_EXP || BOOL_OR_EXP
					//-> REL_EXP && BOOL_OR_EXP
					//-> REL_EXP
		RELATIONAL_EXP,	//-> EQ_EXP > REL_EXP
						//-> EQ_EXP < REL_EXP
						//-> EQ_EXP <= REL_EXP
						//-> EQ_EXP >= REL_EXP
						//-> EQ_EXP
		EQUALITY_EXP,	//-> BIT_EXP == EQ_EXP
						//-> BIT_EXP != EQ_EXP
						//-> BIT_EXP
		BITWISE_EXP,	//-> BITSHIFT_EXP & BIT_EXP
						//-> BITSHIFT_EXP | BIT_EXP
						//-> BITSHIFT_EXP ^ BIT_EXP
						//-> BITSHIFT_EXP
		BITSHIFT_EXP,	//-> ADD_EXP >> BITSHIFT_EXP
						//-> ADD_EXP << BITSHIFT_EXP
						//-> ADD_EXP
		ADDITIVE_EXP,	//-> MULT_EXP + ADD_EXP
						//-> MULT_EXP - ADD_EXP
						//-> MULT_EXP
		MULTIPLICITIVE_EXP,	//-> UNARY_EXP * MULT_EXP
							//-> UNARY_EXP / MULT_EXP
							//-> UNARY_EXP
		UNARY_EXP,	//-> ENCLOSED_EXP
					//-> BIT_NOT
					//-> BOOL_NOT
					//-> DEREFERENCE
					//-> INC
					//-> DEC
					//-> POST_INC
					//-> POST_DEC
					//-> FUNCTION_CALL
					//-> identifier
		BIT_NOT,	//-> ~ UNARY_EXP
		BOOL_NOT,	//-> ! UNARY_EXP
		DEREFERENCE,	//-> * UNARY_EXP
		INCREMENT,	//-> ++ identifier
		DECREMENT,	//-> -- identifier
		POST_INCREMENT,	//-> identifier ++
		POST_DECREMENT,	//-> identifier --
		ARRAY_ACCESSOR,	//-> identifier [ EXPRESSION ]
		ENCLOSED_EXPRESSION,	//-> ( EXPRESSION )

		WHILE_LOOP,
		DOWHILE_LOOP,
		FOR_LOOP,
		IF_ELSE,
		SWITCH,
		SWITCH_CASE,
		CASE,

		BREAK_STATEMENT,
		CONTINUE_STATEMENT,

		LITERAL,

		ASSIGN_OP, //-> = | += | -= | *= | /= | etc

		COMMENT,	//-> comment | block_comment

		EOT,//end of tokens
	};
	void setTokens(vector<Token>* tokens);
	Tree* parse();
private:
	int errors;
	vector<Token>* tokens;
	unsigned int index;

	Token currentToken();
	Token nextToken();
	Token endToken();

	void errorAt(const string& str);
	void error(const string& str);

	Tree* parseGlobalStatement();
	Tree* parseGlobalVarDef();
	Tree* parseDataType();
	Tree* parsePointers();
	Tree* parsePointer();
	Tree* parseLiteral();
	Tree* parseFunctionDef();
	Tree* parseParameterList();
	Tree* parseParameters();
	Tree* parseParameter();
	Tree* parseCodeBlock();
	Tree* parseStatement();
	Tree* parseDefAssignment();
	Tree* parseAssignment();
	Tree* parseAssignOp();
	Tree* parseExpression();
	Tree* parseRelationalExpression();
	Tree* parseEqualityExpression();
	Tree* parseBitwiseExpression();
	Tree* parseBitShiftExpression();
	Tree* parseAdditiveExpression();
	Tree* parseMultiplicitiveExpression();
	Tree* parseUnaryExpression();
	Tree* parseEncloseExpression();
	Tree* parseBitNot();
	Tree* parseBoolNot();
	Tree* parseDereference();
	Tree* parseIncrement();
	Tree* parseDecrement();
	Tree* parsePostIncrement();
	Tree* parsePostDecrement();
	Tree* parseArrayAccessor();
	Tree* parseEnclosedExpression();
	Tree* parseFunctionCall();
	Tree* parseArguments();
	Tree* parseArgument();
	Tree* parseReturnStatement();
	Tree* parseBreakStatement();
	Tree* parseContinueStatement();
	Tree* parseWhileLoop();
	Tree* parseDoWhileLoop();
	Tree* parseForLoop();
	Tree* parseIfElse();
	Tree* parseSwitch();
	Tree* parseSwitchCase();
	Tree* parseCase();
};

#endif