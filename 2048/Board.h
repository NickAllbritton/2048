#pragma once
#include "Tile.h"
#include <random>

class Board
{
public:
	Board(int x, int y, float width, float height);
	~Board() = default;
	void draw(sf::RenderWindow& wnd);
private:
	void drawCell(sf::RenderWindow& wnd, Tile& tile);
	void spawnInitialTiles(int c);
private:
	static constexpr float tileLen = 115.f;
	int width;
	int height;
	sf::RectangleShape backgroundRect;
	std::vector<Tile> tiles;
	std::uniform_real_distribution<float> newTileProb;
};