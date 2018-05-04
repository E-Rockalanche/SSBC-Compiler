#include "ScopeTable.hpp"
#include "TypeManager.hpp"
#include "Debug.hpp"
#include <iostream>
using namespace std;

ScopeTable::ScopeTable(){
	pushScope();
	localScopeSize = 0;
}

void ScopeTable::pushScope(){
	scopeTable.push_back(vector<Entry>());
}

void ScopeTable::popScope(){
	assert(scopeTable.size() > 1, "Trying to pop global scope of ScopeTable");
	localScopeSize -= getCurrentScopeSize();
	scopeTable.pop_back();
}

bool ScopeTable::inGlobalScope(){
	return scopeTable.size() == 1;
}

void ScopeTable::add(string name, Type type, string label,
		unsigned int byteSize){
	dout("adding " << name << ", " << type.toString() << ", " << label << ", "
		<< byteSize);
	assert(name != "", "empty name given to ScopeTable::add()");
	assert(type != Type(), "undefined type given to ScopeTable::add()");
	assert(label != "", "empty label given to ScopeTable::add()");
	assert(byteSize > 0, "size 0 given to ScopeTable::add()");
	
	vector<Entry>& scope = scopeTable.back();
	scope.push_back(Entry(name, type, label, byteSize));

	if (!inGlobalScope()){
		insertLabel(label, byteSize);
	}
}

ScopeTable::Entry ScopeTable::findEntry(string name) const{
	for(int scope = (int)scopeTable.size()-1; scope >= 0; scope--){
		const vector<Entry>& currentScope = scopeTable[scope];
		for(int i = (int)currentScope.size()-1; i >= 0; i--){
			if (currentScope[i].getName() == name){
				return currentScope[i];
			}
		}
	}
	return Entry();
}

Type ScopeTable::getType(string name) const{
	Entry e = findEntry(name);
	if (e.isDefined()){
		return e.getType();
	}else{
		return Type();
	}
}

string ScopeTable::getLabel(string name) const{
	Entry e = findEntry(name);
	if (e.isDefined()){
		return e.getLabel();
	}else{
		return "";
	}
}

bool ScopeTable::isDefined(string name) const{
	return findEntry(name).isDefined();
}

bool ScopeTable::isGlobal(string name) const{
	for(int scope = (int)scopeTable.size()-1; scope >= 0; scope--){
		const vector<Entry>& currentScope = scopeTable[scope];
		for(int i = (int)currentScope.size()-1; i >= 0; i--){
			if (currentScope[i].getName() == name){
				return (scope == 0);
			}
		}
	}
	return false;
}

void ScopeTable::clearEntireScope(){
	clearLocalScope();
	scopeTable.clear();
	pushScope();
}

void ScopeTable::clearLocalScope(){
	scopeTable.resize(1);
	labels.clear();
	localScopeSize = 0;
}

void ScopeTable::insertLabel(string label, unsigned int byteSize){
	unsigned int index = localScopeSize;
	localScopeSize += byteSize;
	if (labels.size() < localScopeSize){
		labels.resize(localScopeSize);
	}
	vector<string>& labelsAtIndex = labels[index];
	labelsAtIndex.push_back(label);
}

unsigned int ScopeTable::getLocalScopeSize() const{
	return localScopeSize;
}

unsigned int ScopeTable::getCurrentScopeSize() const{
	unsigned int size = 0;
	const vector<Entry>& entries = scopeTable.back();
	for(unsigned int i = 0; i < entries.size(); i++){
		size += entries[i].getSize();
	}
	return size;
}

const vector<vector<string>>& ScopeTable::getLocalMemory() const{
	return labels;
}

void ScopeTable::dump() const{
	cout << "========== SCOPE TABLE ==========\n";
	for(unsigned int scope = 0; scope < scopeTable.size(); scope++){
		cout << scope << ":\n";
		const vector<Entry>& curScope = scopeTable[scope];
		for(unsigned int i = 0; i < curScope.size(); i++){
			const Entry& entry = curScope[i];
			cout << entry.getType().toString() << ' ' << entry.getName() << '\n';
		}
	}
}