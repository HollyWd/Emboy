CPPFLAGS= -Wall -funsigned-char -pg -g #flags for compilation
LDFLAGS= -Wall -funsigned-char -pg -g #flags for linking

SRCDIR = src
BUILDDIR = build

disassembler : $(SRCDIR)/disassembler.cpp
	g++ -c $(CPPFLAGS) $(SRCDIR)/disassembler.cpp -o $(BUILDDIR)/disassembler.o

test_Disassembler : $(SRCDIR)/test_Disassembler.cpp $(BUILDDIR)/Disassembler.o
	g++ $(LDFLAGS) $(SRCDIR)/test_Disassembler.cpp $(BUILDDIR)/Disassembler.o -o $(BUILDDIR)/test_Disassembler

$(BUILDDIR)/Disassembler.o : $(SRCDIR)/Disassembler.cpp $(SRCDIR)/Disassembler.hpp
	g++ -c $(CPPFLAGS) $(SRCDIR)/Disassembler.cpp -o $(BUILDDIR)/Disassembler.o

clean :
	# -f will make the remove work even if the files do not exist
	rm -f $(BUILDDIR)/Disassembler.o $(BUILDDIR)/test_Disassembler
