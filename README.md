# The projet

In order better understand computers and optimisation, I decided to try to code a Game Boy emulator. I don't know how far I will go but I will try to record what I learned here.

I chose C++ for this project to gain some experience with this language.

# Disassembling

I start with a simple program converting a binary game boy rom file into assembly code.

## Compile

    $ cd Emboy
    $ mkdir build
    $ g++ -Wall src/disassembler.cpp -o build/disassembler -funsigned-char
    $ ./build/disassembler rom/Zelda.gb

## Notes

First it is funny to note that printing the rom as ascii makes the game dialogs visible:

```Tu as le Violon des Vagues!�Tu as la Conque de l^Ecume!�Tu as la Cloche des Algues!�Tu as la Harpe  du Reflux!�Tu as le        Xylophone Marin!�Tu as le ��anglede Corail!�Tu as l^Orgue   de l^Embellie!�Tu as le Tambourdes Mar*es!�Si tu vois      les pointes,    pense % utiliserton Bouclier.�D^abord un lapinet en dernier,  un spectre...�Si loin...      Ne crains rien. Fonce et vole!�La lueur des    tuiles sera     ton guide...�Plonge l% o=    se croisent     les lumi+res    des flambeaux...�Fracasse        le mur          des Yeux        du Masque!�Le r*bus est    r*solu si les 4 piliers tombent.�Comble tous     les trous avec  le roc qui rouleet cette � est  la solution!�Il y a une      inscription sur le Marbre. Tu nepeux pas la lirecar un Fragment est manquant.```

The rom can also be displayed in hexadecimal with the `hexdump filename` command. The assembly instruction are one to three bytes. The first byte is an opcode identifying the instruction and there can by bytes following for the instruction arguments. For example:

    Bynary code 	Corresponding instruction
    c3 72 28		JP 2872
    7e				LD A (HL)
    1e 02 			LD E 02

I learned that a binary file can't be edited in any text editor, I guess the encoding is stored with the file. In C++, reading in a binary file can be done as follow:
    
	std::ifstream myfilestream(argv[1], std::ios::binary | std::ios::in);
	std::istreambuf_iterator<char> file_it_start(myfilestream), file_it_end;
	std::vector<char> char_vect(file_it_start, file_it_end);

Thus, the binary file can be stored in a vector of bytes.


# Todo
 - Finish desassembling 
 - create disassembler class
 - create cpu class

# Sources 
 - https://realboyemulator.files.wordpress.com
 - http://computerarcheology.com/
 - http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html