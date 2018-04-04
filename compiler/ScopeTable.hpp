#ifndef SCOPE_TABLE_HPP
#define SCOPE_TABLE_HPP

#include <vector>
#include <string>
#include "Type.hpp"
using namespace std;

class ScopeTable{
public:
	ScopeTable();
	void pushScope();
	void popScope();
	void add(string name, Type type);
	bool isDefined(string name) const;
	Type getType(string name) const;
	bool isGlobal(string name) const;
	void clear();
	void dump();
private:
	class Entry{
	public:
		Entry(string varName, Type type){
			this->type = type;
			this->varName = varName;
		}
		Type getType() const {return type;}
		string getName() const {return varName;}
	private:
		Type type;
		string varName;
	};
	vector<vector<Entry>> scopeTable;
};

#endif