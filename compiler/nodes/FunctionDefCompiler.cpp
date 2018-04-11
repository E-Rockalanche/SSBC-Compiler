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

	FunctionSignature sig = funSigComp->getSignature();

	dout("got sig: " << sig.toString());

	sig.setImplemented();

	if (functionManager.addFunction(sig)){
		#if(DEBUG)
			functionManager.dump();
		#endif

		scopeTable.pushScope();
		inMain = (sig == FunctionSignature("main", Type("void")));

		functionReturnType = sig.getReturnType();
		functionReturnLabel = newLabel();
		functionDataLabel = newLabel();
		string returnAddrLabel = newLabel();

		writeComment("########## " + sig.toString() + " ###########");
		if(!inMain){
			//subroutine start
			writeAssembly(sig.toLabel() + ":");

			//temp pop return address
			writeComment("Pop return address to temp");
			writeAssembly("popext16 " + returnAddrLabel);

			//pop parameters
			writeComment("Pop function arguments");
			for(int i = (int)sig.numParams()-1; i >= 0; i--){
				Type type = sig.getParamType(i);
				string varName = sig.getParamName(i);
				string label = newLabel();
				scopeTable.add(varName, type, label);

				if (typeManager.sizeOf(type) == 1){
					writeScopeData(label + ": .byte 0");
					writeAssembly("popext " + label);
				}else{
					writeScopeData(label + ": .word 0");
					writeAssembly("popext16 " + label);
				}
			}

			//push return address
			writeComment("Push return address from temp");
			writeAssembly("pushext16 " + returnAddrLabel);
		}else{
			writeAssembly(".start");
		}

		//compile statements
		writeComment("Function body");
		children[1]->compile();

		if ((functionReturnType != Type("void"))
			&& !children[1]->returnsFromFunction()){
			printError("Control reaches end of non-void function",
				startTokenIndex);
			return false;
		}

		writeComment("Return to call address");
		writeAssembly(functionReturnLabel + ":");
		if (!inMain){
			if (functionReturnType != Type("void")){
				string tempLabel = newLabel();
				writeComment("Pop return address to jump instruction");
				if (typeManager.sizeOf(functionReturnType) == 1){
					writeData(tempLabel + ": .byte 0");
					writeAssembly("popext " + tempLabel);
					writeAssembly("popext16 " + returnAddrLabel);
					writeAssembly("pushext " + tempLabel);
				}else{//size = 2
					writeData(tempLabel + ": .word 0");
					writeAssembly("popext16 " + tempLabel);
					writeAssembly("popext16 " + returnAddrLabel);
					writeAssembly("pushext16 " + tempLabel);
				}
			}else{
				writeAssembly("popext16 " + returnAddrLabel);
			}

			writeAssembly("jump ?");
			writeAssembly(returnAddrLabel + ": .word 0");
		}else{
			writeAssembly("halt");
		}
		writeComment("########## End of " + sig.toString() + " ##########");

		writeComment("Local data to function");
		writeAssembly(functionDataLabel + ":");
		appendScopeDataToAssembly();

		scopeTable.popScope();

		//clear just in case
		functionReturnLabel = "";
		functionReturnType = Type();
		functionDataLabel = "";
		inMain = false;

		return true;
	}else{
		printError("function " + sig.toString() + " is already defined",
			startTokenIndex);
		return false;
	}
}