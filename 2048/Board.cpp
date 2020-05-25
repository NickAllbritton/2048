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
	// initialize all tiles as empty
	for (int y = 0; y < this->height; y++)
	{
		for (int x = 0; x < this->width; x++)
		{
			tiles.at(x + this->width * y).number = 0;
			tiles.at(x + this->width * y).pos = sf::Vector2i(x, y);
		}
	}
	// create a few numbered tiles
	spawnInitialTiles(3);
}

Tile& Board::getTile(sf::Vector2i pos)
{
	return tiles.at(pos.x + width * pos.y);
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

void Board::move(Direction dir)
{
	switch (dir)
	{
	case Direction::Left:
		{
			// start from the left and move every tile as far as it can go.
			// if it is at x = 0 it can't be moved further left. so start at x = 1
			// CHECK IF TILE IS EMPTY.........
			// 1. look to tile to the left
			// 2. if it is not empty, that means it and everything to the left of it is already as far as it can go
			// 3. if it is empty, go back to one and check tile left of this one..
			// 4. if its number matches yours merge with it
			// 5. if its number is different go to or stay at the tile to your right
			for (int x = 1; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					if (getTile(sf::Vector2i(x, y)).number != 0)
					{
						int x1 = x - 1;
						while (x1 >= 0)
						{
							if (tiles.at(x1 + width * y).number == tiles.at(x + width * y).number) // same number
								tiles.at(x + width * y).merge(tiles, tiles.at(x1 + width * y), width);
							else if (tiles.at(x1 + width * y).number == 0) // if it is empty
							{
								if (x1 != 0) x1 -= 1;
								else // do not check the next over it doesn't exist...
								{
									tiles.at(x1 + width * y).number = tiles.at(x + width * y).number;
									if (x1 != x) tiles.at(x + width * y).number = 0; // this number should be empty if you 
																					// are moving from there
									break;
								}
							}
							else // if the tile has a different number
							{
								tiles.at((x1 + 1) + width * y).number = tiles.at(x + width * y).number;
								if (x1 != x) tiles.at(x + width * y).number = 0; // this number should be empty if you 
																				// are moving from there
							}
						}
					}
					else continue;
				}
			}
		}
		break;
	case Direction::Right:
		{
			// start from the right and move every tile as far as it can go.
			// if it is at x = width - 1 it can't be moved further right. so start at x = width - 2
			// CHECK IF TILE IS EMPTY.........
			// 1. look to tile to the right
			// 2. if it is not empty, that means it and everything to the right of it is already as far as it can go
			// 3. if it is empty, go back to step 1. and check tile to the right of this one..
			// 4. if its number matches yours merge with it
			// 5. if its number is different go to or stay at the tile to your left
			for (int x = width - 2; x >= 0; x--)
			{
				for (int y = 0; y < height; y++)
				{
					if (getTile(sf::Vector2i(x, y)).number != 0)
					{
						int x1 = x + 1;
						while (x1 <= width - 1)
						{
							if (tiles.at(x1 + width * y).number == tiles.at(x + width * y).number) // same number
								tiles.at(x + width * y).merge(tiles, tiles.at(x1 + width * y), width);
							else if (tiles.at(x1 + width * y).number == 0) // if it is empty
							{
								if (x1 != width - 1) x1 += 1;
								else // do not check the next over it doesn't exist...
								{
									tiles.at(x1 + width * y).number = tiles.at(x + width * y).number;
									if (x1 != x) tiles.at(x + width * y).number = 0; // this number should be empty if you 
																					// are moving from there
									break;
								}
							}
							else // if the tile has a different number
							{
								tiles.at((x1 - 1) + width * y).number = tiles.at(x + width * y).number;
								if (x1 != x) tiles.at(x + width * y).number = 0; // this number should be empty if you 
																				 // are moving from there
							}
						}
					}
					else continue;
				}
			}
		}
		break;
	case Direction::Up:
		{
			// start from the left and move every tile as far as it can go.
			// if it is at y = 0 it can't be moved further up. so start at y = 1
			// CHECK IF TILE IS EMPTY.........
			// 1. look to above tile
			// 2. if it is not empty, that means it and everything above it is already as far as it can go
			// 3. if it is empty, go back to one and check tile above this one..
			// 4. if its number matches yours merge with it
			// 5. if its number is different go to or stay at the tile below
			for (int y = 1; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					if (getTile(sf::Vector2i(x, y)).number != 0)
					{
						int y1 = y - 1;
						while (y1 >= 0)
						{
							if (tiles.at(x + width * y1).number == tiles.at(x + width * y).number) // same number
								tiles.at(x + width * y).merge(tiles, tiles.at(x + width * y1), width);
							else if (tiles.at(x + width * y1).number == 0) // if it is empty
							{
								if (y1 != 0) y1 -= 1;
								else // do not check the next over it doesn't exist...
								{
									tiles.at(y1 + width * y).number = tiles.at(x + width * y).number;
									if (y1 != x) tiles.at(x + width * y).number = 0; // this number should be empty if you 
																					// are moving from there
									break;
								}
							}
							else // if the tile has a different number
							{
								tiles.at(x + width * (y1 + 1)).number = tiles.at(x + width * y).number;
								if (y1 != y) tiles.at(x + width * y).number = 0; // this number should be empty if you 
																				// are moving from there
							}
						}
					}
					else continue;
				}
			}
		}
		break;
	case Direction::Down:
		{
			// start from the left and move every tile as far as it can go.
			// if it is at y = height - 1 it can't be moved further down. so start at y = height - 2
			// CHECK IF TILE IS EMPTY.........
			// 1. look to below tile
			// 2. if it is not empty, that means it and everything above it is already as far as it can go
			// 3. if it is empty, go back to step 1. and check tile below this one..
			// 4. if its number matches yours merge with it
			// 5. if its number is different go to or stay at the tile above
			for (int y = height - 2; y >= 0; y++)
			{
				for (int x = 0; x < width; x++)
				{
					if (getTile(sf::Vector2i(x, y)).number != 0)
					{
						int y1 = y + 1;
						while (y1 <= height - 1)
						{
							if (tiles.at(x + width * y1).number == tiles.at(x + width * y).number) // same number
								tiles.at(x + width * y).merge(tiles, tiles.at(x + width * y1), width);
							else if (tiles.at(x + width * y1).number == 0) // if it is empty
							{
								if (y1 != height - 1) y1 += 1;
								else // do not check the next over it doesn't exist...
								{
									tiles.at(y1 + width * y).number = tiles.at(x + width * y).number;
									if (y1 != x) tiles.at(x + width * y).number = 0; // this number should be empty if you 
																						// are moving from there
									break;
								}
							}
							else // if the tile has a different number
							{
								tiles.at(x + width * (y1 - 1)).number = tiles.at(x + width * y).number;
								if (y1 != y) tiles.at(x + width * y).number = 0; // this number should be empty if you 
																					 // are moving from there
							}
						}
					}
					else continue;
				}
			}
		}
		break;
	}
	spawnTile(dir);
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

void Board::spawnTile(Direction dir)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<int> tileLoc(0, 3);
	switch (dir)
	{
	case Direction::Left:
		{
			sf::Vector2i pos;
			do // set pos = to a random cell on right side of board
			{
				pos = sf::Vector2i(width - 1, tileLoc(rng));
			} while (tiles.at(pos.x + pos.y * width).number != 0); // if the tile is occupied do it again
			int tileValue = newTileProb(rng) < .9f ? 2 : 4; // tileValue has a 90% chance of being a 2
			tiles.at(pos.x + width * pos.y) = Tile(pos, tileValue); // set the tile at pos to a new tile with tileValue
		}
		break;
	case Direction::Right:
		{
			sf::Vector2i pos;
			do // set pos = to a random cell on left side of board
			{
				pos = sf::Vector2i(0, tileLoc(rng));
			} while (tiles.at(pos.x + pos.y * width).number != 0); // if the tile is occupied do it again
			int tileValue = newTileProb(rng) < .9f ? 2 : 4; // tileValue has a 90% chance of being a 2
			tiles.at(pos.x + width * pos.y) = Tile(pos, tileValue); // set the tile at pos to a new tile with tileValue
		}
		break;
	case Direction::Up:
		{
			sf::Vector2i pos;
			do // set pos = to a random cell on bottom of board
			{
				pos = sf::Vector2i(tileLoc(rng), height - 1);
			} while (tiles.at(pos.x + pos.y * width).number != 0); // if the tile is occupied do it again
			int tileValue = newTileProb(rng) < .9f ? 2 : 4; // tileValue has a 90% chance of being a 2
			tiles.at(pos.x + width * pos.y) = Tile(pos, tileValue); // set the tile at pos to a new tile with tileValue
		}
		break;
	case Direction::Down:
		{
			sf::Vector2i pos;
			do // set pos = to a random cell on top of board
			{
				pos = sf::Vector2i(tileLoc(rng), 0);
			} while (tiles.at(pos.x + pos.y * width).number != 0); // if the tile is occupied do it again
			int tileValue = newTileProb(rng) < .9f ? 2 : 4; // tileValue has a 90% chance of being a 2
			tiles.at(pos.x + width * pos.y) = Tile(pos, tileValue); // set the tile at pos to a new tile with tileValue
		}
		break;
	}
}
