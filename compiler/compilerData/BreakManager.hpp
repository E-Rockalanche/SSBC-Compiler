#ifndef BREAK_MANAGER_HPP
#define BREAK_MANAGER_HPP

#include <string>
#include <vector>
using namespace std;

class BreakManager{
public:
	void pushSwitch(string endLabel);
	void pushLoop(string endLabel, string startLabel);
	string getStartLabel() const;
	string getEndLabel() const;
	void popScope();
	bool inLoop() const;
	bool inScope() const;
private:
	class Scope{
	public:
		Scope(string endLabel);
		Scope(string endLabel, string startLabel);
		string getStartLabel() const;
		string getEndLabel() const;
		bool isLoop() const;
	private:
		string endLabel;
		string startLabel;
	};

	vector<Scope> scopeStack;

	void assertNonEmpty() const;
};

#endif