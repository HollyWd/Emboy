

#### Markdown cheat sheet
https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet

#### Compile
make disassembler
./build/disassembler rom/Zelda.gb

make emulator
./build/emulator rom/Zelda.gb

### Documentation
doxygen Doxyfile

#### Git
- add all tracked files to commit : `git add -u`

#### Debug
`$g++ -Wall main.cpp -o my_prog -g #Compile with -g option`
`$gdb ./my_prog`

#### profile
`$g++ main.cpp -o my_prog -pg `
`$gprof test gmon.out > analysis.txt`

#### Dump hexa
`$hexdump filename`

#### GB
16 bit adress : 0000 -> FFFF
http://z80-heaven.wikidot.com/instructions-set:set
