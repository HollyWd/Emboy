
#include <SFML/Graphics.hpp>
#include <vector>

const int TILE_SIZE=8;
const int SCREEN_SIZE=256;

struct Color{
	sf::Uint8 r=0;
	sf::Uint8 g=0;
	sf::Uint8 b=0;
};


class Video {
	private: 
		const std::vector<char> memory;		
		sf::Texture bg_texture;
		sf::Sprite bg_sprite;

		sf::Texture get_tile(uint16_t addr);

	public:
		sf::RenderWindow window;

		Video(const std::vector<char>& mem);
		void update_bg();
};
