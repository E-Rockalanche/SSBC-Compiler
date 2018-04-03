#include "ParseTree.hpp"

//Tree

bool Tree::isLeaf(){
	throw runtime_error("Cannot call isLeaf() on base class Tree");
}
Tree::~Tree(){}

//Leaf

Leaf::Leaf(unsigned int tokenIndex){
	index = tokenIndex;
}
bool Leaf::isLeaf(){
	return true;
}
unsigned int Leaf::getTokenIndex(){
	return index;
}

//Branch

Branch::Branch(int type){
	this->type = type;
}
bool Branch::isLeaf(){
	return false;
}
int Branch::getType(){
	return type;
}
Tree* Branch::at(unsigned int index){
	return children[index];
}
unsigned int Branch::size(){
	return children.size();
}
Branch& Branch::addChild(Tree* child){
	children.push_back(child);
	return *this;
}
Branch::~Branch(){
	for(unsigned int i = 0; i < children.size(); i++)
		delete children[i];
}