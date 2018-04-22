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
	void add(string name, Type type, string label, unsigned int byteSize);
	bool isDefined(string name) const;
	Type getType(string name) const;
	string getLabel(string name) const;
	bool isGlobal(string name) const;
	void clearEntireScope();
	void clearLocalScope();
	void dump() const;
	unsigned int getLocalScopeSize() const;
	const vector<vector<string>>& getLocalMemory() const;
private:
	class Entry{
	public:
		Entry(){
			type = Type();
			varName = "";
			label = "";
			size = 0;
		}
		Entry(string varName, Type type, string label, unsigned int size){
			this->type = type;
			this->varName = varName;
			this->label = label;
			this->size = size;
		}
		Type getType() const {return type;}
		string getName() const {return varName;}
		string getLabel() const {return label;}
		unsigned int getSize() const {return size;}
		bool isDefined(){
			return (type != Type()
				&& varName != ""
				&& label != ""
				&& size != 0);
		}
	private:
		Type type;
		string varName;
		string label;
		unsigned int size;
	};
	vector<vector<Entry>> scopeTable;
	vector<vector<string>> labels;
	unsigned int localScopeSize;

	Entry findEntry(string name) const;
	unsigned int getCurrentScopeSize() const;
	void insertLabel(string label, unsigned int byteSize);
};

#endif