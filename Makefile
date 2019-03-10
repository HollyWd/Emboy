CPPFLAGS= -Wall -funsigned -char -pg -g
LDFLAGS= -Wall -funsigned -char -pg -g

SRCDIR = src

test_disassembler : $(SRCDIR)/test_disassembler.cpp Disassembler.o
	g++ $(LDFLAGS) $(SRCDIR)/test_disassembler.cpp Disassembler.o -o test_disassembler

Disassembler.o : $(SRCDIR)/Disassembler.cpp $(SRCDIR)/Disassembler.hpp
	g++ $(LDFLAGS) $(SRCDIR)/Disassembler.cpp $(SRCDIR)/Disassembler.h -o Disassembler.o

clean :
	rm -f Disassembler.o test_disassembler