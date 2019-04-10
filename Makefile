CPPFLAGS= -Wall -funsigned-char -pg -g #flags for compilation
LDFLAGS= -Wall -funsigned-char -pg -g #flags for linking

SRCDIR = src
BUILDDIR = build

disassembler : $(SRCDIR)/disassembler.cpp $(BUILDDIR)/Disassembler.o
	g++ $(CPPFLAGS) $(SRCDIR)/disassembler.cpp $(BUILDDIR)/Disassembler.o -o $(BUILDDIR)/disassembler


test_cpu : $(SRCDIR)/test_cpu.cpp $(BUILDDIR)/Cpu.o
	g++ $(LDFLAGS) $(SRCDIR)/test_cpu.cpp $(BUILDDIR)/Cpu.o -o $(BUILDDIR)/test_cpu

$(BUILDDIR)/Cpu.o : $(SRCDIR)/Cpu.cpp $(SRCDIR)/Cpu.hpp
	g++ -c $(CPPFLAGS) $(SRCDIR)/Cpu.cpp -o $(BUILDDIR)/Cpu.o

test_Disassembler : $(SRCDIR)/test_Disassembler.cpp $(BUILDDIR)/Disassembler.o
	g++ $(LDFLAGS) $(SRCDIR)/test_Disassembler.cpp $(BUILDDIR)/Disassembler.o -o $(BUILDDIR)/test_Disassembler

$(BUILDDIR)/Disassembler.o : $(SRCDIR)/Disassembler.cpp $(SRCDIR)/Disassembler.hpp
	g++ -c $(CPPFLAGS) $(SRCDIR)/Disassembler.cpp -o $(BUILDDIR)/Disassembler.o



clean :
	# -f will make the remove work even if the files do not exist
	rm -f $(BUILDDIR)/Disassembler.o $(BUILDDIR)/test_Disassembler $(BUILDDIR)/disassembler.o $(BUILDDIR)/disassembler
