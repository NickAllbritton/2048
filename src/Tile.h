#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile() = default;
	Tile(sf::Vector2i pos, int number);
	void merge(std::vector<Tile>& board, Tile& tile, int width);
	int number = 0;
	sf::Vector2i pos = sf::Vector2i(0, 0);
};
