CC = g++
CPPFLAGS= -Wall -funsigned-char -pg -g #flags for compilation
LDFLAGS= -Wall -funsigned-char -pg -g -lsfml-graphics -lsfml-window -lsfml-system #flags for linking

#SRCS = $(shell find src -name "*.cpp") #use the shell find function that lists all files in src folder following the "*.cpp" regular expression
#OBJS = $(patsubst %.cpp, %.o, $(src))
#HEADERS = $(shell find src -name "*.hpp")

SRCDIR = src
BUILDDIR = build
INC = -I$(SRCDIR) -I$(SRCDIR)/tests

#$^ = list of dependancies of upper line
#$@ = target name

display : $(BUILDDIR)/display.o $(BUILDDIR)/Cpu.o $(BUILDDIR)/Video.o $(BUILDDIR)/utils.o
	$(CC) $^ -o $(BUILDDIR)/$@  $(LDFLAGS)
	#$(CC) $(LDFLAGS) $^ -o $(BUILDDIR)/$@ 

disassembler : $(SRCDIR)/disassembler.cpp $(BUILDDIR)/Disassembler.o $(BUILDDIR)/utils.o
	$(CC) $(LDFLAGS) $^ -o $(BUILDDIR)/$@ 


emulator : $(SRCDIR)/emulator.cpp $(BUILDDIR)/Cpu.o $(BUILDDIR)/Disassembler.o $(BUILDDIR)/utils.o 
	$(CC) $(LDFLAGS) $^ -o $(BUILDDIR)/$@ 

test_cpu : $(SRCDIR)/test_cpu.cpp $(BUILDDIR)/Cpu.o
	$(CC) $(LDFLAGS) $^ -o $(BUILDDIR)/$@ 

test_disassembler : $(SRCDIR)/test_disassembler.cpp $(BUILDDIR)/Disassembler.o
	$(CC) $(LDFLAGS) $^ -o $(BUILDDIR)/$@ 

test_emulator : $(SRCDIR)/tests/test_emulator.cpp $(BUILDDIR)/Test.o $(BUILDDIR)/Cpu.o $(BUILDDIR)/Disassembler.o $(BUILDDIR)/utils.o 
	$(CC) $(LDFLAGS) ${INC}  $^ -o $(BUILDDIR)/$@ 

## Build object files	
#TODO fix .o destination (is src while should be build)
$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp $(SRCDIR)/utils.hpp 
	$(CC) -c $(CPPFLAGS) ${INC} $< -o $@
# For all targets finishing by .o, build them with the cpp and hpp of the same name
# -c = only compile as object file, not as exe
# $< = first item in dependancies list

$(BUILDDIR)/%.o : $(SRCDIR)/tests/%.cpp $(SRCDIR)/tests/%.hpp 
	$(CC) -c $(CPPFLAGS) ${INC} $< -o $@


clean :
	# -f will make the remove work even if the files do not exist
	rm -f $(BUILDDIR)/* 
