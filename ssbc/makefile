PROGRAM = ../ssbc.exe
INCLUDE = -I ../tool
CFLAGS = -Wall -Wextra
LFLAGS = -static
CXX = g++

$(PROGRAM):	ssbc.cpp ssbc.hpp main.cpp ../tool/Debug.hpp
	$(CXX) $(CFLAGS) $(LFLAGS) $(INCLUDE) ssbc.cpp main.cpp -o $@