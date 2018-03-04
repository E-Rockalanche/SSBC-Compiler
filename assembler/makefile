PROGRAM = ssbca.exe
INCLUDE = -I ../lang -I ../tokenizer -I ../tool
CFLAGS = -c -Wall -Wextra
LFLAGS = -static
CXX = g++
MAKE_OBJ = $(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

$(PROGRAM):	obj/main.o obj/LabelList.o obj/SSBCAssembler.o obj/SSBCLang.o\
		../tool/obj/Assert.o ../tokenizer/obj/Tokenizer.o\
		../tokenizer/obj/Scanner.o obj/Binary.o
	$(CXX) $(LFLAGS) $^ -o $@

obj/main.o:	main.cpp SSBCAssembler.hpp ../tool/Debug.hpp
	$(MAKE_OBJ)

obj/LabelList.o:	LabelList.cpp LabelList.hpp ../tool/Debug.hpp
	$(MAKE_OBJ)

obj/SSBCAssembler.o:	SSBCAssembler.cpp SSBCAssembler.hpp SSBCLang.hpp\
		../tokenizer/Tokenizer.hpp ../tool/Assert.hpp ../tool/Debug.hpp\
		Binary.hpp
	$(MAKE_OBJ)

obj/SSBCLang.o:	SSBCLang.cpp SSBCLang.hpp ../lang/Lang.hpp ../tool/Debug.hpp
	$(MAKE_OBJ)

../tool/obj/Assert.o:	../tool/Assert.cpp ../tool/Assert.hpp
	$(MAKE_OBJ)

../tokenizer/obj/Tokenizer.o:	../tokenizer/Tokenizer.cpp\
		../tokenizer/Tokenizer.hpp ../tokenizer/Scanner.hpp ../tool/Assert.hpp\
		../tool/Debug.hpp
	$(MAKE_OBJ)

../tokenizer/obj/Scanner.o:	../tokenizer/Scanner.cpp ../tokenizer/Scanner.hpp
	$(MAKE_OBJ)

obj/Binary.o:	Binary.cpp Binary.hpp
	$(MAKE_OBJ)

clean:
	del obj\*.o $(PROGRAM)

test.exe:	obj/TestLang.o obj/SSBCLang.o
	$(CXX) $(LFLAGS) $^ -o $@

SSBCAssembler.asm:	SSBCAssembler.cpp SSBCAssembler.hpp SSBCLang.hpp\
		../tokenizer/Tokenizer.hpp ../tool/Assert.hpp ../tool/Debug.hpp\
		Binary.hpp
	$(MAKE_OBJ) -S