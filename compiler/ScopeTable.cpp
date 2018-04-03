#include "ScopeTable.hpp"
#include "Debug.hpp"

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
	dout("ScopeTable::add(" << name << ", " << type.toString() << ")");

	vector<Entry>& scope = scopeTable.back();

	dout("current scope size = " << scope.size());

	scope.push_back(Entry(name, type));
}

Type ScopeTable::getType(string name) const{
	dout("ScopeTable::getType(" << name << ")");

	for(int scope = (int)scopeTable.size()-1; scope >= 0; scope--){
		const vector<Entry>& currentScope = scopeTable[scope];
		for(int i = (int)currentScope.size()-1; i >= 0; i--){
			if (currentScope[i].getName() == name){
				return currentScope[i].getType();
			}
		}
	}
	return Type();
}

bool ScopeTable::isDefined(string name) const{
	return getType(name).isDefined();
}

bool ScopeTable::isGlobal(string name) const{
	dout("ScopeTable::isGlobal(" << name << ")");

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