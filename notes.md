

# Markdown cheat sheet
https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet

#Compile
`g++ -Wall disassembler.cpp -o ../build/disassembler -pg -g -funsigned-char
`
`../build/disassembler toto`

-Wall = warnings exigents
-funsigned-char : define char as unsigned

#Debug
`$g++ -Wall main.cpp -o my_prog -g #Compile with -g option`
`$gdb ./my_prog`

#profile
`$g++ main.cpp -o my_prog -pg `
`$gprof test gmon.out > analysis.txt`

#Dump hexa
hexdump file

#GB
16 bit adress : 0000 -> FFFF
http://z80-heaven.wikidot.com/instructions-set:set