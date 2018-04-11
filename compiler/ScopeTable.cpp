#include "ScopeTable.hpp"
#include "TypeManager.hpp"
#include "Debug.hpp"
#include <iostream>
using namespace std;

ScopeTable::ScopeTable(){
	pushScope();
}

void ScopeTable::pushScope(){
	vector<Entry> newScope;
	scopeTable.push_back(newScope);
}

void ScopeTable::popScope(){
	assert(scopeTable.size() > 1, "Trying to pop global scope of scope table");
	scopeTable.pop_back();
}

bool ScopeTable::inGlobalScope(){
	return scopeTable.size() == 1;
}

void ScopeTable::add(string name, Type type, string label){
	assert(name != "", "empty name given to ScopeTable::add()");
	assert(type != Type(), "undefined type given to ScopeTable::add()");
	assert(label != "", "empty label given to ScopeTable::add()");
	vector<Entry>& scope = scopeTable.back();
	scope.push_back(Entry(name, type, label));
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

void ScopeTable::clear(){
	scopeTable.clear();
	pushScope();
}

void ScopeTable::dump(){
	cout << "========== SCOPE TABLE ==========\n";
	for(unsigned int scope = 0; scope < scopeTable.size(); scope++){
		cout << scope << ":\n";
		const vector<Entry>& curScope = scopeTable[scope];
		for(unsigned int i = 0; i < curScope.size(); i++){
			const Entry& entry = curScope[i];
			cout << entry.getType().toString() << ' ' << entry.getName() << '\n';
		}
	}
	cout << "=================================\n";
}

vector<Type> ScopeTable::getScopeTypes() const{
	vector<Type> types;
	for(unsigned int scope = 0; scope < scopeTable.size(); scope++){
		const vector<Entry>& curScope = scopeTable[scope];
		for(unsigned int i = 0; i < curScope.size(); i++){
			types.push_back(curScope[i].getType());
		}
	}
	return types;
}