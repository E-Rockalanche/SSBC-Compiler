#include "ScopeTable.hpp"
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

void ScopeTable::add(string name, Type type){
	vector<Entry>& scope = scopeTable.back();
	scope.push_back(Entry(name, type));
}

Type ScopeTable::getType(string name) const{
	Type type;
	for(int scope = (int)scopeTable.size()-1; scope >= 0; scope--){
		const vector<Entry>& currentScope = scopeTable[scope];
		for(int i = (int)currentScope.size()-1; i >= 0; i--){
			if (currentScope[i].getName() == name){
				type = currentScope[i].getType();
				dout("type of " << name << " is " << type.toString());
			}
		}
	}
	if (!type.isDefined()){
		dout(name << " is not defined");
	}
	return type;
}

bool ScopeTable::isDefined(string name) const{
	return getType(name).isDefined();
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