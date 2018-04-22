#include "CompilerNode.hpp"

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