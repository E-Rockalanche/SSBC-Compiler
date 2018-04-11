#ifndef SWITCH_COMPILER_HPP
#define SWITCH_COMPILER_HPP

#include "BaseCompiler.hpp"
#include "SwitchCaseCompiler.hpp"
#include "Assert.hpp"

class SwitchCompiler : public CompilerNode {
public:
	~SwitchCompiler();
	bool parse();
	bool compile();

private:
	class Case{
	public:
		Case();
		Case(int constant, string label, SwitchCaseCompiler* compiler);
		bool isDefined();
		int getConstant();
		string getLabel();
		bool operator<(const Case& other);
		bool compile();
		unsigned int getIndex();
		int getValue();
		bool returnsFromFunction();

	private:
		int constant;
		string label;
		SwitchCaseCompiler* compiler;

		void assertDefined();
	};

	vector<Case> sortedCases;
	unsigned int typeSize;
	string defaultLabel;
	string tempLabel;
	string endLabel;

	void compileSwitch(int low, int high);
};

#endif