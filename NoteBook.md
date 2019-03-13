# Notebook

Here I am going to log what I learned and the blocking points of this development.

**Table of content**
1. [Disassembling](#Disassembling)
2. [Compilation](#Compilation)

## Disassembling

I start with a simple program converting a binary game boy rom file into assembly code.

### Rom content

First it is funny to note that printing the rom as ascii makes the game dialogs visible:

```Tu as le Violon des Vagues!�Tu as la Conque de l^Ecume!�Tu as la Cloche des Algues!�Tu as la Harpe  du Reflux!�Tu as le        Xylophone Marin!�Tu as le ��anglede Corail!�Tu as l^Orgue   de l^Embellie!�Tu as le Tambourdes Mar*es!�Si tu vois      les pointes,    pense % utiliserton Bouclier.�D^abord un lapinet en dernier,  un spectre...�Si loin...      Ne crains rien. Fonce et vole!�La lueur des    tuiles sera     ton guide...�Plonge l% o=    se croisent     les lumi+res    des flambeaux...�Fracasse        le mur          des Yeux        du Masque!�Le r*bus est    r*solu si les 4 piliers tombent.�Comble tous     les trous avec  le roc qui rouleet cette � est  la solution!�Il y a une      inscription sur le Marbre. Tu nepeux pas la lirecar un Fragment est manquant.```

The rom can also be displayed in hexadecimal with the `hexdump filename` command. **Each assembly instruction is encoded in one to three bytes**. The first byte is an opcode identifying the instruction and there can by bytes following for the instruction arguments. Thus, hte first byte make us able to know how many arguments we should expect and which byte is the following opcode. For example, the following bytes `c3 72 28 7e 1e 02` will be desassembled as:

    Bynary code 	Corresponding instruction
    c3 72 28      JP 2872
    7e            LD A (HL)
    1e 02         LD E 02

### Binary files

I learned that a binary file can't be edited in any text editor because it will probably store '1001 1110' as a string... GEdit seems to store the encoding of files in its own cache since the encoding is not stored in the file itself. I do not know how sublimetext decides to decode a file. I suspect it uses the frequency of the bytes to guess what encoding is used. Indeed, some bytes are recurent in a text file while other never appear.

In C++, reading in a binary file can be done as follow:
    
	std::ifstream myfilestream(argv[1], std::ios::binary | std::ios::in);
	std::istreambuf_iterator<char> file_it_start(myfilestream), file_it_end;
	std::vector<char> char_vect(file_it_start, file_it_end);

Thus, the binary file can be stored in a vector of bytes.

### Iterating through the bytes
I used an iterator at first but this cause me some troubles. Indeed, when I jump several opbytes, I can get out the vector of byte without the system noticing it. So I have to check on every iteration that I am still it the vector (see below) and I find it ugly... I plan to use the `[]` operator for vectors with an index when I will emulate the CPU. Moreover, the CPU will have a program counter `PC` register that will serve as an array index. 

	std::vector<char>::iterator it = char_vect.begin();

	while (it!=char_vect.end()){
		try{
			std::cout<<"0x"<<std::hex<<std::setfill('0') << std::setw(2)<<(int)*it<<" ";
			it+=disassemble(it);
			//check that it do not overpass end
			if (size_t(it - char_vect.begin())>char_vect.size()){
				throw "Try to disassemble instruction outside of memory bounds";
			}
		}
		catch(const char * c){
			std::cerr << "Fatal error: " << c << std::endl;
			return 1;
		}
	}

## Compilation

### g++

### Makefile
