#include "FunctionDefCompiler.hpp"
#include "FunctionSignatureCompiler.hpp"
#include "TypeCompiler.hpp"
#include "StatementSequenceCompiler.hpp"

FunctionDefCompiler::~FunctionDefCompiler(){}

bool FunctionDefCompiler::parse(){
	P_BEGIN
	P_ADD_NODE(new FunctionSignatureCompiler())
	P_EXPECT_TOKEN(CppLang::OPEN_BRACE)
	P_ADD_NODE(new StatementSequenceCompiler())
	P_EXPECT_TOKEN(CppLang::CLOSE_BRACE)
	P_END
}

bool FunctionDefCompiler::compile(){
	dout("Compiling in " << __FILE__);
	assert(children.size() == 2, "no function definition");

	FunctionSignatureCompiler* funSigComp
		= static_cast<FunctionSignatureCompiler*>(children[0]);

	mySignature = funSigComp->getSignature();

	dout("got mySignature: " << mySignature.toString());

	mySignature.setImplemented();

	if (functionManager.addFunction(mySignature)){
		#if(DEBUG)
			functionManager.dump();
		#endif

		scopeTable.pushScope();
		isMain = (mySignature == FunctionSignature("main", Type("void")));

		setStaticData();

		dout("Compiling function start");

		writeComment("########## " + mySignature.toString() + " ###########");

		compileFunctionStart();

		dout("Compiling function body");

		//compile statements
		writeComment("Function body");
		children[1]->compile();

		if ((functionReturnType != Type("void"))
			&& !children[1]->returnsFromFunction()){
			printError("Control reaches end of non-void function",
				startTokenIndex);
			return false;
		}

		dout("Compiling return from function");

		compileFunctionEnd();

		writeComment("########## End of " + mySignature.toString() + " ##########");

		compileLocalMemory();

		//clear just in case
		functionReturnLabel = "";
		functionReturnType = Type();
		functionDataLabel = "";
		isMain = false;

		return true;
	}else{
		printError("function " + mySignature.toString() + " is already defined",
			startTokenIndex);
		return false;
	}
}

void FunctionDefCompiler::setStaticData(){
	dout("Setting static function data");

	functionReturnType = mySignature.getReturnType();
	functionReturnLabel = newLabel();
	functionDataLabel = newLabel();
	returnAddrLabel = newLabel();
}

void FunctionDefCompiler::compileFunctionStart(){
	dout("mySig = " << mySignature.toLabel());

	if (isMain){
		writeAssembly(".start");
	}else{
		//subroutine start
		writeAssembly(mySignature.toLabel() + ":");

		dout("returnAddrLabel = " << returnAddrLabel);

		//temp pop return address
		writeComment("Pop return address to temp");
		writeAssembly("popext16 " + returnAddrLabel);

		dout("Popping function arguments");

		compileArguments();

		//push return address
		writeComment("Push return address from temp");
		writeAssembly("pushext16 " + returnAddrLabel);
	}

	dout("Finished compiling function start");
}

void FunctionDefCompiler::compileArguments(){
	dout("compiling arguments");
	//pop parameters
	writeComment("Pop function arguments");

	dout("number of arguments = " << mySignature.numParams());

	for(int i = (int)mySignature.numParams()-1; i >= 0; i--){
		Type type = mySignature.getParamType(i);
		dout("type = " << type.toString());

		string varName = mySignature.getParamName(i);
		dout("name = " << varName);

		string label = newLabel();
		dout("label = " << label);

		unsigned int typeSize = typeManager.sizeOf(type);
		dout("size = " << typeSize);

		scopeTable.add(varName, type, label, typeSize);

		if (typeSize == 1){
			writeAssembly("popext " + label);
		}else{
			writeAssembly("popext16 " + label);
		}
	}
}

void FunctionDefCompiler::compileFunctionEnd(){
	dout("compiling function end");

	writeComment("Return to call address");
	writeAssembly(functionReturnLabel + ":");
	if (!isMain){
		if (functionReturnType != Type("void")){
			string tempLabel = newLabel();
			writeComment("Pop return address to jump instruction");
			unsigned int retValSize = typeManager.sizeOf(functionReturnType);
			writeGlobalData(tempLabel + ": .array " + to_string(retValSize));
			popToAddress(tempLabel, retValSize);
			writeAssembly("popext16 " + returnAddrLabel);
			pushFromAddress(tempLabel, retValSize);
		}else{
			writeAssembly("popext16 " + returnAddrLabel);
		}

		writeAssembly("jump ?");
		writeAssembly(returnAddrLabel + ": .word 0");
	}else{
		writeAssembly("halt");
	}
}

void FunctionDefCompiler::compileLocalMemory(){
	writeComment("Local data to function");
	writeAssembly(functionDataLabel + ":");
	dout("Writing local memory");
	const vector<vector<string>>& lifetimeScope = scopeTable.getLocalMemory();
	for(unsigned int byte = 0; byte < lifetimeScope.size(); byte++){
		const vector<string>& labels = lifetimeScope[byte];
		string line;
		if (labels.size() == 0){
			line = newLabel() + ": ";
		}else{
			for(unsigned int i = 0; i < labels.size(); i++){
				line += labels[i] + ": ";
			}
		}
		writeAssembly(line + ".byte 0");
	}
	writeComment("End of local memory");

	scopeTable.clearLocalScope();
}