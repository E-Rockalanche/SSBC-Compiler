#include "CompilerNode.hpp"

CompilerNode::~CompilerNode(){
	for(unsigned int i = 0; i < children.size(); i++){
		if(children[i] != NULL){
			delete children[i];
		}
	}
}

unsigned int CompilerNode::getIndex(){
	return startTokenIndex;
}

void CompilerNode::setIndex(unsigned int startIndex) {
	startTokenIndex = startIndex;
}