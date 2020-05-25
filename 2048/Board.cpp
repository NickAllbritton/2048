#include "Board.h"

Board::Board(int x, int y, float width, float height) 
	: 
	width(x), height(y), tiles(x*y), newTileProb(0.f, 1.f),
	backgroundRect(sf::Vector2f((tileLen + 1.f) * static_cast<float>(x) - 1.f,
	((tileLen + 1.f)* static_cast<float>(y) - 1.f))) // rectangle with x*y tiles with 1 pixel spacing between each cell
{
	backgroundRect.setPosition(sf::Vector2f(width / 2 - backgroundRect.getSize().x / 2,
		height / 2 - backgroundRect.getSize().y / 2 + 40.f)); // center the rectangle but slightly lower in y
	backgroundRect.setFillColor(sf::Color(70, 70, 70));
	// create a few numbered tiles
	spawnInitialTiles(3);
}

void Board::draw(sf::RenderWindow& wnd)
{
	// draw background rectangle
	wnd.draw(backgroundRect);
	// draw tiles
	for (auto tile : tiles)
	{
		drawCell(wnd, tile);
	}
}

void Board::drawCell(sf::RenderWindow& wnd, Tile& tile)
{
	sf::Vector2f topLeftOfBoard = backgroundRect.getPosition();
	if (tile.number != 0)
	{
		sf::RectangleShape rect(sf::Vector2f(tileLen, tileLen));
		rect.setPosition(sf::Vector2f(topLeftOfBoard.x + tile.pos.x * (tileLen + 1.f),
			topLeftOfBoard.y + tile.pos.y * (tileLen + 1.f))); //sets position of tile in screen coordinates
		rect.setFillColor(sf::Color::Magenta); // change color later
		wnd.draw(rect);
	}
}

void Board::spawnInitialTiles(int c)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<int> tileLoc(0, 3);
	for (int i = 0; i < c; i++)
	{
		sf::Vector2i pos;
		do // set pos = to a random cell
		{
			pos = sf::Vector2i(tileLoc(rng), tileLoc(rng));
		} while (tiles.at(pos.x + pos.y * width).number != 0); // if the tile is occupied do it again
		int tileValue = newTileProb(rng) < .9f ? 2 : 4; // tileValue has a 90% chance of being a 2
		tiles.at(pos.x + width * pos.y) = Tile(pos, tileValue); // set the tile at pos to a new tile with tileValue
	}
}
