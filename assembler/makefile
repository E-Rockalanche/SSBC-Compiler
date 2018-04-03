PROGRAM = ssbca.exe
INCLUDE = -I ../lang -I ../tokenizer -I ../tool
CFLAGS = -c -Wall -Wextra
LFLAGS = -static
CXX = g++
OBJ_DIR = ../obj
MAKE_OBJ = $(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

$(PROGRAM):	$(OBJ_DIR)/AssemblerMain.o $(OBJ_DIR)/LabelList.o $(OBJ_DIR)/SSBCAssembler.o $(OBJ_DIR)/SSBCLang.o $(OBJ_DIR)/Assert.o $(OBJ_DIR)/Tokenizer.o $(OBJ_DIR)/Scanner.o $(OBJ_DIR)/Binary.o
	$(CXX) $(LFLAGS) $^ -o $@

$(OBJ_DIR)/AssemblerMain.o:	AssemblerMain.cpp SSBCAssembler.hpp ../tool/Debug.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/LabelList.o:	LabelList.cpp LabelList.hpp ../tool/Debug.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/SSBCAssembler.o:	SSBCAssembler.cpp SSBCAssembler.hpp SSBCLang.hpp ../tokenizer/Tokenizer.hpp ../tool/Assert.hpp ../tool/Debug.hpp Binary.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/SSBCLang.o:	SSBCLang.cpp SSBCLang.hpp ../lang/Lang.hpp ../tool/Debug.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/Assert.o:	../tool/Assert.cpp ../tool/Assert.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/Tokenizer.o:	../tokenizer/Tokenizer.cpp 	../tokenizer/Tokenizer.hpp ../tokenizer/Scanner.hpp ../tool/Assert.hpp ../tool/Debug.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/Scanner.o:	../tokenizer/Scanner.cpp ../tokenizer/Scanner.hpp
	$(MAKE_OBJ)

$(OBJ_DIR)/Binary.o:	Binary.cpp Binary.hpp
	$(MAKE_OBJ)

clean:
	del ..\obj\*.o $(PROGRAM)