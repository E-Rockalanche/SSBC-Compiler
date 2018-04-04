PROGRAM = ../compiler.exe
INCLUDE = -I../lang -I../tokenizer -I../tool -I../assembler -I./nodes -I.
CFLAGS = -c -Wall -Wextra
LFLAGS = -static -Wall -Wextra
CXX = g++
OBJ_DIR = ../obj
MAKE_OBJ = $(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

CMP_SOURCES = ${wildcard nodes/*.cpp}
CMP_OBJECTS = ${CMP_SOURCES:.cpp=.o}
CMP_HEADERS = ${CMP_SOURCES:.cpp=.hpp}

$(PROGRAM):	$(OBJ_DIR)/CppLang.o $(OBJ_DIR)/Tokenizer.o $(OBJ_DIR)/Scanner.o \
		$(OBJ_DIR)/Assert.o $(OBJ_DIR)/ScopeTable.o $(OBJ_DIR)/Main.o \
		$(OBJ_DIR)/TypeManager.o $(OBJ_DIR)/Type.o \
		$(OBJ_DIR)/FunctionManager.o $(OBJ_DIR)/FunctionSignature.o \
		$(OBJ_DIR)/LabelList.o $(OBJ_DIR)/SSBCAssembler.o $(OBJ_DIR)/SSBCLang.o \
		$(OBJ_DIR)/Binary.o $(CMP_OBJECTS) 
	$(CXX) $(LFLAGS) $^ -o $@

nodes/%.o:	nodes/%.cpp FunctionManager.hpp FunctionSignature.hpp \
		ScopeTable.hpp Type.hpp TypeManager.hpp ../tokenizer/Token.hpp \
		CppLang.hpp CompilerDebug.hpp nodes/BaseCompiler.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/Main.o:	Main.cpp nodes/Compiler.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/ScopeTable.o:	ScopeTable.cpp ScopeTable.hpp Type.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/TypeManager.o:	TypeManager.cpp TypeManager.hpp Type.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/Type.o:	Type.cpp Type.hpp ../tool/Assert.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/CppLang.o:	CppLang.cpp CppLang.hpp ../lang/Lang.hpp \
		CompilerDebug.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/FunctionSignature.o:	FunctionSignature.cpp FunctionSignature.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/FunctionManager.o:	FunctionManager.cpp FunctionManager.hpp \
		FunctionSignature.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/Assert.o:	../tool/Assert.cpp ../tool/Assert.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/Tokenizer.o:	../tokenizer/Tokenizer.cpp ../tokenizer/Tokenizer.hpp \
		../tokenizer/Scanner.hpp ../tool/Assert.hpp CompilerDebug.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/Scanner.o:	../tokenizer/Scanner.cpp ../tokenizer/Scanner.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/LabelList.o:	../assembler/LabelList.cpp ../assembler/LabelList.hpp \
		CompilerDebug.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/SSBCAssembler.o:	../assembler/SSBCAssembler.cpp \
		../assembler/SSBCAssembler.hpp ../assembler/SSBCLang.hpp \
		../tokenizer/Tokenizer.hpp ../tool/Assert.hpp CompilerDebug.hpp \
		../assembler/Binary.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/SSBCLang.o:	../assembler/SSBCLang.cpp ../assembler/SSBCLang.hpp \
		../lang/Lang.hpp CompilerDebug.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/Binary.o:	../assembler/Binary.cpp ../assembler/Binary.hpp
	$(MAKE_OBJ)

clean:
	del ..\obj\*.o $(PROGRAM) nodes\*.o