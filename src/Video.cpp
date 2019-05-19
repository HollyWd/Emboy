#include "Video.hpp"

Video::Video(const std::vector<char>& mem): 
	memory(mem)
{
	window.create(sf::VideoMode(SCREEN_SIZE,SCREEN_SIZE), "Video Window");
	window.clear(sf::Color(0, 0, 0, 255));
	bg_texture.create(SCREEN_SIZE,SCREEN_SIZE);

	bg_sprite= sf::Sprite(bg_texture);
}

void Video::update_bg(){
	std::vector<sf::Uint8> pixels(SCREEN_SIZE*SCREEN_SIZE*4,255);
	bg_texture.update(pixels.data());
	bg_sprite= sf::Sprite(bg_texture);
	window.draw(bg_sprite);
	window.draw(sf::Sprite(get_tile(0x8000)));
	window.display();

}

sf::Texture Video::get_tile(uint16_t addr){

	//std::vector<char>::const_iterator it = memory.begin();


	//Fill the tile data
	std::vector<unsigned char> tile(TILE_SIZE*TILE_SIZE*4,255);
	//iterate through the tile pixels
	for(int i=0;i<TILE_SIZE; i++){ //line
		for(int j=0;j<TILE_SIZE; j++){ //row
			int screen_buffer_index = (i*TILE_SIZE+j)*4;
			int memory_index = (i*TILE_SIZE+j)/4;
			int bit_index = ((i*TILE_SIZE+j)%4)*2;
			char color_code = (memory[addr+memory_index] & (0xC000>>bit_index)) >>(6-bit_index); //mask with 1100 0000
			//Color color = 
			tile[screen_buffer_index]=color_code*255;
			tile[screen_buffer_index+1]=0;
			tile[screen_buffer_index+2]=0;
		}
	}

	//Make a texture from it
	sf::Texture tile_texture;
	tile_texture.create(TILE_SIZE,TILE_SIZE);
	tile_texture.update(tile.data());
	return tile_texture;
}