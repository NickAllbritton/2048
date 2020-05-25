#pragma once
#include <sfml.hpp>

class Tile
{
public:
	Tile() = default;
	Tile(sf::Vector2i pos, int number);
	int number = 0;
	sf::Vector2i pos = sf::Vector2i(0, 0);
};