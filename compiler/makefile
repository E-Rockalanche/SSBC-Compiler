PROGRAM = compiler.exe
INCLUDE = -I ../lang -I ../tokenizer -I ../tool
CFLAGS = -c -Wall -Wextra
LFLAGS = -static
CXX = g++
MAKE_OBJ = $(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

$(PROGRAM):	obj/testMain.o obj/CppLang.o ../tokenizer/obj/tokenizer.o\
		../tokenizer/obj/Scanner.o ../tool/obj/Assert.o
	$(CXX) $(LFLAGS) $^ -o $@

obj/testMain.o:	testMain.cpp CppLang.hpp ../tokenizer/Token.hpp\
		../tokenizer/Tokenizer.hpp
	$(MAKE_OBJ)

obj/CppLang.o:	CppLang.cpp CppLang.hpp ../lang/Lang.hpp ../tool/Debug.hpp
	$(MAKE_OBJ)

../tool/obj/Assert.o:	../tool/Assert.cpp ../tool/Assert.hpp
	$(MAKE_OBJ)

../tokenizer/obj/Tokenizer.o:	../tokenizer/Tokenizer.cpp\
		../tokenizer/Tokenizer.hpp ../tokenizer/Scanner.hpp ../tool/Assert.hpp\
		../tool/Debug.hpp
	$(MAKE_OBJ)

../tokenizer/obj/Scanner.o:	../tokenizer/Scanner.cpp ../tokenizer/Scanner.hpp
	$(MAKE_OBJ)

clean:
	del obj\*.o $(PROGRAM)