#include "BreakManager.hpp"
#include "Assert.hpp"

void BreakManager::pushSwitch(string endLabel){
	scopeStack.push_back(Scope(endLabel));
}

void BreakManager::pushLoop(string endLabel, string startLabel){
	scopeStack.push_back(Scope(endLabel, startLabel));
}

string BreakManager::getStartLabel() const{
	assertNonEmpty();
	for(int i = scopeStack.size()-1; i >= 0; i--){
		const Scope& scope = scopeStack[i];
		if(scope.isLoop()){
			return scope.getStartLabel();
		}
	}
	return "";
}

string BreakManager::getEndLabel() const{
	assertNonEmpty();
	return scopeStack.back().getEndLabel();
}

bool BreakManager::inLoop() const{
	if (scopeStack.size() > 0){
		return (getStartLabel() != "");
	}else{
		return false;
	}
}

bool BreakManager::inScope() const{
	return (scopeStack.size() > 0);
}

void BreakManager::popScope(){
	assertNonEmpty();
	scopeStack.pop_back();
}

void BreakManager::assertNonEmpty() const{
	assert(scopeStack.size() > 0, "Break manager stack is empty");
}



BreakManager::Scope::Scope(string endLabel){
	this->endLabel = endLabel;
	startLabel = "";
}
BreakManager::Scope::Scope(string endLabel, string startLabel){
	this->endLabel = endLabel;
	this->startLabel = startLabel;
}
string BreakManager::Scope::getStartLabel() const{
	assert(startLabel != "", "Cannot get start label of non-loop scope");
	return startLabel;
}
string BreakManager::Scope::getEndLabel() const{
	return endLabel;
}
bool BreakManager::Scope::isLoop() const{
	return startLabel != "";
}