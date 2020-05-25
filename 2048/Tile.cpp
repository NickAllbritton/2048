#include "Tile.h"

Tile::Tile(sf::Vector2i pos, int number) : pos(pos), number(number) {}

void Tile::merge(std::vector<Tile> board, Tile& tile, int width)
{
	board.at(pos.x + width * pos.y) = board.at(tile.pos.x + width * tile.pos.y);
	number += tile.number;
	tile.number = 0;
}
