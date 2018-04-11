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
	bool inGlobalScope();
	void add(string name, Type type, string label);
	bool isDefined(string name) const;
	Type getType(string name) const;
	string getLabel(string name) const;
	bool isGlobal(string name) const;
	void clear();
	void dump();
	
	//returns list of types of all variables in local scope
	vector<Type> getScopeTypes() const;
private:
	class Entry{
	public:
		Entry(){}
		Entry(string varName, Type type, string label){
			this->type = type;
			this->varName = varName;
			this->label = label;
		}
		Type getType() const {return type;}
		string getName() const {return varName;}
		string getLabel() const {return label;}
		bool isDefined(){
			return (type != Type() && varName != "" && label != "");
		}
	private:
		Type type;
		string varName;
		string label;
	};
	vector<vector<Entry>> scopeTable;

	Entry findEntry(string name) const;
};

#endif