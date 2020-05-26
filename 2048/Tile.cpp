#include "Tile.h"

Tile::Tile(sf::Vector2i pos, int number) : pos(pos), number(number) {}

void Tile::merge(std::vector<Tile>& board, Tile& tile, int width)
{
	board.at(pos.x + width * pos.y).number = tile.number * 2;
	tile.number = 0;
}
