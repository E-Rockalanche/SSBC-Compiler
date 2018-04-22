MAKE = mingw32-make

all:	./compiler ./assembler ./ssbc
	
./compiler:
	$(MAKE) -C $@

./assembler:
	$(MAKE) -C $@

./ssbc:
	$(MAKE) -C $@

.PHONY: all	./compiler ./assembler ./ssbc