#ifndef PARSE_TREE_HPP
#define PARSE_TREE_HPP

#include <stdexcept>
#include <vector>
using namespace std;

class Tree{
public:
	virtual bool isLeaf();
	virtual ~Tree();
};

class Leaf : public Tree{
public:
	Leaf(unsigned int index);
	bool isLeaf();
	unsigned int getTokenIndex();
	int getType();
private:
	unsigned int index;
};

class Branch : public Tree{
public:
	Branch(int type);
	bool isLeaf();
	int getType();
	Tree* at(unsigned int index);
	unsigned int size();
	Branch& addChild(Tree* child);
	~Branch();
private:
	int type;
	vector<Tree*> children;
};

#endif