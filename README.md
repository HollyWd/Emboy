# The projet

In order better understand computers and optimisation, I decided to try to code a Game Boy emulator. I don't know how far I will go but I will try to record what I learned here.

I chose C++ for this project to gain some experience with this language. This is developped on Ubuntu 18.

## Progress

I start with a simple program converting a binary game boy rom file into assembly code. The dessasembler implement about 75% of the instructions right now.

## Compile and test
The current disassembler is working however it is not complete and can be compiled and test as following. It prints the assembly code from the binary rom and a message error for the instruction that are not implemented yet.

    $ cd Emboy
    $ mkdir build
    $ g++ -Wall src/disassembler.cpp -o build/disassembler -funsigned-char
    $ ./build/disassembler rom/Zelda.gb

# Todo
 - Finish desassembling 
 - Encapsulate disassembling into a class
 - Create a cpu class

# Sources 
 - https://realboyemulator.files.wordpress.com
 - http://computerarcheology.com/
 - http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
