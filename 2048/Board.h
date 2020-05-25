#pragma once
#include "Tile.h"
#include <random>

enum class Direction
{
	Left,
	Right,
	Up,
	Down
};

class Board
{
public:
	Board(int x, int y, float width, float height);
	~Board() = default;
	Tile& getTile(sf::Vector2i pos);
	void draw(sf::RenderWindow& wnd);
	void move(Direction dir);
private:
	void drawCell(sf::RenderWindow& wnd, Tile& tile);
	void spawnInitialTiles(int c);
	void spawnTile(Direction dir);
private:
	static constexpr float tileLen = 115.f;
	int width;
	int height;
	sf::RectangleShape backgroundRect;
	std::vector<Tile> tiles;
	std::uniform_real_distribution<float> newTileProb;
};