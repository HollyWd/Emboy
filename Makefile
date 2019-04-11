CPPFLAGS= -Wall -funsigned-char -pg -g #flags for compilation
LDFLAGS= -Wall -funsigned-char -pg -g #flags for linking

#SRCS = $(shell find src -name "*.cpp") #use the shell find function that lists all files in src folder following the "*.cpp" regular expression
#OBJS = $(patsubst %.cpp, %.o, $(src))
#HEADERS = $(shell find src -name "*.hpp")

SRCDIR = src
BUILDDIR = build

disassembler : $(SRCDIR)/disassembler.cpp $(BUILDDIR)/Disassembler.o
	g++ $(CPPFLAGS) $^ -o $(BUILDDIR)/$@ 
#$^ = list of dependancies of upper line
#$@ = target name

emulator : $(SRCDIR)/emulator.cpp $(SRCDIR)/Cpu.o $(SRCDIR)/Disassembler.o $(SRCDIR)/utils.o 
	g++ $(CPPFLAGS) $^ -o $(BUILDDIR)/$@ 

test_cpu : $(SRCDIR)/test_cpu.cpp $(BUILDDIR)/Cpu.o
	g++ $(CPPFLAGS) $^ -o $(BUILDDIR)/$@ 

test_disassembler : $(SRCDIR)/test_Disassembler.cpp $(BUILDDIR)/Disassembler.o
	g++ $(LDFLAGS) $(SRCDIR)/test_Disassembler.cpp $(BUILDDIR)/Disassembler.o -o $(BUILDDIR)/test_Disassembler

## Build object files	
#TODO fix .o destination (is src while should be build)
$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp $(SRCDIR)/%.hpp
	g++ -c $(CPPFLAGS) $< -o $@
# For all targets finishing by .o, build them with the cpp and hpp of the same name
# -c = only compile as object file, not as exe
# $< = first item in dependancies list


clean :
	# -f will make the remove work even if the files do not exist
	rm -f $(BUILDDIR)/*
