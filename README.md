# The projet

In order better understand computers and optimisation, I decided to try to code a Game Boy emulator. I don't know how far I will go but I will try to record what I learned here.

I chose C++ for this project to gain some experience with this language. This is developped on Ubuntu 18.

## Progress

I start with a simple program converting a binary game boy rom file into assembly code. Proportion of the instruction implemented:

Disassembled instructions: 100%
Emulated instructions: 23% (115/501)    Tested Instructions: 3% (16/501)

## Compile and test
The disassembler is working and can be compiled and test as following. 

    $ cd Emboy
    $ mkdir build
    $ make disassembler
    $ ./build/disassembler rom/tetris.gb

However this disassembler, since it can't recognise a data zone, tries to disassemble those bytes and stops when it runs into an opcode it doesnt know (which is actually not an opcode but data).

The current emulator can be compiled and run with the following command.

    $ make emulator
    $ ./build/emulator rom/tetris.gb

Press `s` to disassemble and emulate the next instruction. The instruction that are not emulated yet will print `Instruction not implemented yet` and the program counter is incremented.

# Todo

 - Finish emulating the CPU instruction
 - Test the instructions
 - Emulate graphic hardware

# Sources 
 - https://realboyemulator.files.wordpress.com
 - http://computerarcheology.com/
 - http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
