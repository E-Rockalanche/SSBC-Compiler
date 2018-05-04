#include "SwitchCompiler.hpp"
#include "SwitchCaseCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include <utility>
#include <algorithm>
#include <map>
using namespace std;

SwitchCompiler::~SwitchCompiler(){}

bool SwitchCompiler::parse(){
	P_BEGIN
	P_EXPECT_TOKEN(CppLang::SWITCH)
	P_EXPECT_TOKEN(CppLang::OPEN_PAREN)
	P_ADD_NODE(new ExpressionCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_PAREN)
	P_EXPECT_TOKEN(CppLang::OPEN_BRACE)
	P_LOOP_NODE(new SwitchCaseCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_BRACE)
	P_END
}

bool SwitchCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(children.size() >= 1, "No switch statement");

	children[0]->compile();
	Type expType = children[0]->getType();
	typeSize = typeManager.sizeOf(expType);

	if ((!typeManager.isPrimitive(expType) && !expType.isPointer())
		|| typeSize == 0){
		printError("Cannot switch type " + expType.toString(),
			startTokenIndex + 2);
		return false;
	}

	tempLabel = newLabel();
	endLabel = newLabel();
	defaultLabel = endLabel;

	map<int, unsigned int> caseStartIndicies;
	vector<Case> cases;
	Case defaultCase;

	for(unsigned int i = 1; i < children.size(); i++){
		SwitchCaseCompiler* caseCompiler
			= static_cast<SwitchCaseCompiler*>(children[i]);

		if (caseCompiler->isDefaultCase()){
			if (defaultCase.isDefined()){
				printError("Default case is already defined",
					caseCompiler->getIndex());
				printError("Case was defined", defaultCase.getIndex());
			}else{
				defaultLabel = newLabel();
				defaultCase = Case(0, defaultLabel, caseCompiler);
				cases.push_back(defaultCase);
			}
		}else{
			//not default case
			int constant = caseCompiler->getValue();
			if (caseStartIndicies[constant] > 0){
				printError("Case already defined", caseCompiler->getIndex());
				printError("Case was defined", caseStartIndicies[constant]);
			}else{
				caseStartIndicies[constant] = caseCompiler->getIndex();
				Case curCase = Case(constant, newLabel(), caseCompiler);
				cases.push_back(curCase);
				sortedCases.push_back(curCase);
			}
		}
	}

	sort(sortedCases.begin(), sortedCases.end());

	string popOperation = (typeSize == 1) ? "popext" : "popext16";
	writeAssembly(popOperation + " " + tempLabel);

	compileSwitch(0, sortedCases.size() - 1);

	string tempType = (typeSize == 1) ? ".byte" : ".word";
	writeAssembly(tempLabel + ": " + tempType + " 0");

	breakManager.pushSwitch(endLabel);

	//compile cases
	for(unsigned int i = 0; i < cases.size(); i++){
		writeAssembly(cases[i].getLabel() + ":");
		cases[i].compile();
	}

	breakManager.popScope();

	writeAssembly(endLabel + ":");

	return true;
}

void SwitchCompiler::compileSwitch(int low, int high){
	if (low > high){
		writeAssembly("jump " + defaultLabel);
		return;
	}
	int mid = (low + high)/2;
	assert(mid < (int)sortedCases.size() && mid >= 0,
		"index to sortedCases out of range. Index = " + to_string(mid));
	Case curCase = sortedCases[mid];

	string notCase = newLabel();
	string positiveCase = newLabel();

	if (typeSize == 1){
		writeAssembly("pushimm " + to_string(curCase.getValue()));
		writeAssembly("pushext " + tempLabel);
		writeAssembly("sub");
		writeAssembly("popinh");
	}else{
		writeAssembly("pushimm16 " + to_string(curCase.getValue()));
		writeAssembly("pushext16 " + tempLabel);
		writeAssembly("jsr SUB16");
		writeAssembly("jsr TEST16");
		writeAssembly("popext PSW");
		writeAssembly("popinh16");
	}
	
	writeAssembly("jnz " + notCase);

	//match
	writeAssembly("jump " + curCase.getLabel());

	writeAssembly(notCase + ": jnn " + positiveCase);
	//negative case
	compileSwitch(low, mid - 1);

	writeAssembly(positiveCase + ":");
	compileSwitch(mid + 1, high);
}

bool SwitchCompiler::endsStatementSequence() {
	return false;
}

bool SwitchCompiler::returnsFromFunction() {
	bool hasDefault = false;
	for(unsigned int i = 1; i < children.size(); i++) {
		SwitchCaseCompiler c = static_cast<SwitchCaseCompiler>children[i];
		if (!c->returnsFromFunction()) {
			return false;
		} else if (c->isDefaultCase()) {
			hasDefault = true;
		}
	}
	return hasDefault;
}





SwitchCompiler::Case::Case(){
	constant = 0;
	label = "";
	compiler = NULL;
}
SwitchCompiler::Case::Case(int constant, string label, SwitchCaseCompiler* compiler){
	this->constant = constant;
	this->label = label;
	this->compiler = compiler;
}
bool SwitchCompiler::Case::isDefined(){
	return (compiler != NULL && label != "");
}
void SwitchCompiler::Case::assertDefined(){
	assert(isDefined(), "Case compiler is not defined");
}
int SwitchCompiler::Case::getConstant(){
	assertDefined();
	return constant;
}
string SwitchCompiler::Case::getLabel(){
	assertDefined();
	return label;
}
bool SwitchCompiler::Case::operator<(const Case& other){
	assertDefined();
	return constant < other.constant;
}
bool SwitchCompiler::Case::compile(){
	assertDefined();
	return compiler->compile();
}
unsigned int SwitchCompiler::Case::getIndex(){
	assertDefined();
	return compiler->getIndex();
}
int SwitchCompiler::Case::getValue(){
	assertDefined();
	return compiler->getValue();
}