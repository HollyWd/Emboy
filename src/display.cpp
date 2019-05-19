#include <SFML/Graphics.hpp>
#include "Cpu.hpp"
#include "Disassembler.hpp"
#include "Video.hpp"

// const TILE_WIDTH=36;
// const PIXEL_WIDTH = 256;

// std::vector<sf::Uint8> getBackGroundPixels(std::vector<char> memory){

// 	std::vector<sf::Uint8> pixel_buffer(PIXEL_WIDTH*PIXEL_WIDTH,0);

// 	uint_16 addr = 0x9800;
// 	for(int i=0;i<TILE_WIDTH;i++){
// 		for(int j=0;j<TILE_WIDTH;j++){
// 			//Get tile address
// 			uint8_t data_addr = memory[addr];
// 			//Read tile color
// 			for(int m=0;m<8;m++){
// 				for(int n=0;n<8;n++){
// 					pixel_buffer[i*TILE_WIDTH*8+j*TILE_WIDTH*8+] //compliqué, raisoner plustot par tile à mettre à jour, commencer par une image de une tile 
// 				}
// 			}

			
// 		}
// 	}
// }

int main(int argc, char* argv[]){

	// Create objects
	std::cout << "Let's emulate!"<<std::endl;
	//Disassembler dis;
	Cpu cpu;


	//Load cartidge into CPU memory
	cpu.load_cartridge(argv[1]);
	std::cout << "Cartridge file is "<< argv[1]<<std::endl;
	std::cout << "Cartridge loaded!"<<std::endl<<std::endl;



	cpu.print_cartridge_info();

	cpu.print_mem(0x8000, 100, true);

	//Create Video

	Video video(cpu.get_memory());
	sf::RenderWindow & window = video.window;



	// int height=256;
	// int width=256;

	// sf::RenderWindow window(sf::VideoMode(width,height),"MyWindow");

	// std::vector<sf::Uint8> data_array(width*height*4,255);

	// std::vector<sf::Uint8> background = getBackGroundPixels(cpu.get_memory());

	// sf::Texture texture;
	// if (!texture.create(32,32)){
	// 	return EXIT_FAILURE;
	// }
	//texture.update(data_array.data(),0,0,200,200);
	// texture.update(data_array.data()); 

	// sf::Sprite sprite(texture);

	// sf::Font font;
	// if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")){
	// 	return EXIT_FAILURE;
	// }
	// sf::Text text("Hello World!", font, 80);
	// 
	

	while(window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}
		video.update_bg();
		// window.clear(sf::Color(0, 0, 0, 255));
		// window.draw(sprite);
		// //window.draw(text);
		// window.display();
	}
}