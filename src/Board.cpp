#include "Board.h"
#include "SavedGame.h"
#include <iostream>

Board::Board(int x, int y, float width, float height, std::string name) 
	: 
	width(x), height(y), tiles(x*y), newTileProb(0.f, 1.f), name(name),
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
	// populate the board for a new game or load the game "name"
	spawnInitialTiles();
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

void Board::move(Direction dir, std::vector<std::pair<Direction, bool>> canMove)
{

	switch (dir)
	{
	// to move left
	// 1. loop through x's from left to right until you find an occupied cell
	// 2. loop through all tiles to the left of it until you get to an occupied cell or the wall
	// 3. if you reach the wall or a different number cell move to the cell to the right. set old cell to empty
	// 4. if you reach a cell that matches your number merge into it. set old cell to empty
	// 5. repeat
	case Direction::Left:
		// optimization: start from x = 1. tiles at x = 0 can't move further left
		for (sf::Vector2i pos(1, 0); pos.x < width; pos.x++)
		{
			for (pos.y = 0; pos.y < height; pos.y++)
			{
				if (getTile(pos).number != 0) // step 1: ignore empty cells
				{
					// step 2: get location of next occupied cell (or wall which is x = -1)
					sf::Vector2i newPos = nextTile(pos, dir);
					// step 3: if newPos is left wall
					if (newPos.x == -1)
					{
						// move tile to tile to the right of newPos
						newPos.x += 1;
						moveTile(pos, newPos);
					}
					// step 3: if tile at newPos is a different numbered cell
					else if (getTile(newPos).number != getTile(pos).number)
					{
						// move tile to tile to the right of newPos
						newPos.x += 1;
						moveTile(pos, newPos);
					}
					// step 4: if tile at newPos has same number
					else if (getTile(newPos).number == getTile(pos).number)
					{
						// merge into it
						getTile(newPos).merge(tiles, getTile(pos), width);
					}
					// repeat for all occupied cells
				}
			}
		}
		break;
		// to move right
		// 1. loop through x's from right to left until you find an occupied cell
		// 2. loop through all tiles to the right of it until you get to an occupied cell or the wall
		// 3. if you reach the wall or a different number cell move to the cell to the left. set old cell to empty
		// 4. if you reach a cell that matches your number merge into it. set old cell to empty
		// 5. repeat
	case Direction::Right:
		// optimization: start from x = width - 2. tiles at x = width - 1 can't move further right
		for (sf::Vector2i pos(width - 2, 0); pos.x >= 0; pos.x--)
		{
			for (pos.y = 0; pos.y < height; pos.y++)
			{
				if (getTile(pos).number != 0) // step 1: ignore empty cells
				{
					// step 2: get location of next occupied cell (or wall which is x = width)
					sf::Vector2i newPos = nextTile(pos, dir);
					// step 3: if newPos is right wall
					if (newPos.x == width)
					{
						// move tile to tile to the left of newPos
						newPos.x -= 1;
						moveTile(pos, newPos);
					}
					// step 3: if tile at newPos is a different numbered cell
					else if (getTile(newPos).number != getTile(pos).number)
					{
						// move tile to tile to the left of newPos
						newPos.x -= 1;
						moveTile(pos, newPos);
					}
					// step 4: if tile at newPos has same number
					else if (getTile(newPos).number == getTile(pos).number)
					{
						// merge into it
						getTile(newPos).merge(tiles, getTile(pos), width);
					}
					// repeat for all occupied cells
				}
			}
		}
		break;
	// to move up
	// 1. loop through y's from top to bottom until you find an occupied cell
	// 2. loop through all tiles above it until you get to an occupied cell or the wall
	// 3. if you reach the wall or a different number cell move to the cell below. set old cell to empty
	// 4. if you reach a cell that matches your number merge into it. set old cell to empty
	// 5. repeat
	case Direction::Up:
		// optimization: start from y = 1. tiles at y = 0 can't move further up
		for (sf::Vector2i pos(0, 1); pos.y < height; pos.y++)
		{
			for (pos.x = 0; pos.x < width; pos.x++)
			{
				if (getTile(pos).number != 0) // step 1: ignore empty cells
				{
					// step 2: get location of next occupied cell (or wall which is y = -1)
					sf::Vector2i newPos = nextTile(pos, dir);
					// step 3: if newPos is top wall
					if (newPos.y == -1)
					{
						// move tile to 1 tile below newPos
						newPos.y += 1;
						moveTile(pos, newPos);
					}
					// step 3: if tile at newPos is a different numbered cell
					else if (getTile(newPos).number != getTile(pos).number)
					{
						// move tile to tile below newPos
						newPos.y += 1;
						moveTile(pos, newPos);
					}
					// step 4: if tile at newPos has same number
					else if (getTile(newPos).number == getTile(pos).number)
					{
						// merge into it
						getTile(newPos).merge(tiles, getTile(pos), width);
					}
					// repeat for all occupied cells
				}
			}
		}
		break;
	// to move up
	// 1. loop through y's from bottom to top until you find an occupied cell
	// 2. loop through all tiles below it until you get to an occupied cell or the wall
	// 3. if you reach the wall or a different number cell move to the cell above. set old cell to empty
	// 4. if you reach a cell that matches your number merge into it. set old cell to empty
	// 5. repeat
	case Direction::Down:
		// optimization: start from y = height - 2. tiles at y = height - 1 can't move further down
		for (sf::Vector2i pos(0, height - 2); pos.y >= 0; pos.y--)
		{
			for (pos.x = 0; pos.x < width; pos.x++)
			{
				if (getTile(pos).number != 0) // step 1: ignore empty cells
				{
					// step 2: get location of next occupied cell (or wall which is y = height)
					sf::Vector2i newPos = nextTile(pos, dir);
					// step 3: if newPos is bottom wall
					if (newPos.y == height)
					{
						// move tile to 1 tile above newPos
						newPos.y -= 1;
						moveTile(pos, newPos);
					}
					// step 3: if tile at newPos is a different numbered cell
					else if (getTile(newPos).number != getTile(pos).number)
					{
						// move tile to tile above newPos
						newPos.y -= 1;
						moveTile(pos, newPos);
					}
					// step 4: if tile at newPos has same number
					else if (getTile(newPos).number == getTile(pos).number)
					{
						// merge into it
						getTile(newPos).merge(tiles, getTile(pos), width);
					}
					// repeat for all occupied cells
				}
			}
		}
		break;
	}
	if(canMove.at(static_cast<int>(dir)).second) spawnTile(dir); // spawn a tile if the move was valid
}

bool Board::nextTileAvailable(sf::Vector2i pos, Direction dir)
{
	// holds next tile over but value depends on the direction of movment
	sf::Vector2i nextPos;
	switch (dir)
	{
	case Direction::Left:
		nextPos = sf::Vector2i(pos.x - 1, pos.y);
		break;
	case Direction::Right:
		nextPos = sf::Vector2i(pos.x + 1, pos.y);
		break;
	case Direction::Up:
		nextPos = sf::Vector2i(pos.x, pos.y - 1);
		break;
	case Direction::Down:
		nextPos = sf::Vector2i(pos.x, pos.y + 1);
		break;
	}

	// return whether the next tile over is available to move into if it is on the board
	return contains(nextPos) && (getTile(nextPos).number == 0 || getTile(pos).number == getTile(nextPos).number);
}

void Board::drawCell(sf::RenderWindow& wnd, Tile& tile)
{
	sf::Vector2f topLeftOfBoard = backgroundRect.getPosition();
	if (tile.number != 0)
	{
		sf::RectangleShape rect(sf::Vector2f(tileLen, tileLen));
		rect.setPosition(sf::Vector2f(topLeftOfBoard.x + tile.pos.x * (tileLen + 1.f),
			topLeftOfBoard.y + tile.pos.y * (tileLen + 1.f))); //sets position of tile in screen coordinates
		rect.setFillColor(sf::Color(130, 130, 80));

		sf::Font oneday;
		oneday.loadFromFile("../resources/ONEDAY.ttf");

		sf::Text number;

		number.setFont(oneday);
		number.setCharacterSize(tileLen / 2.f);
		number.setFillColor(sf::Color::White);
		number.setString(std::to_string(tile.number));
		number.setPosition(sf::Vector2f(rect.getPosition().x + tileLen / 2.f - number.getLocalBounds().width / 2.f,
			rect.getPosition().y + tileLen / 2.f - number.getLocalBounds().height / 1.2f));

		wnd.draw(rect);
		wnd.draw(number);
	}
}

void Board::spawnInitialTiles()
{
	if(name == "new")
	{
		int numInitialTiles = 3;
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<int> tileLoc(0, 3);
		for (int i = 0; i < numInitialTiles; i++)
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
	else // then load the saved game
	{
		for(auto& game : readSavedGames("../resources/saved_games.xml"))
		{
			if(name == game.name) 
			{
				std::vector<int> tiles;
				tiles = game.tiles; // store the tile numbers of the game being loaded
				for(int i = 0; i < tiles.size(); i++)
				{


					// x + wy = i 
					// x = i - wy
					// so ...
					int x = i % width;
					// once we've found x, we can solve directly for y
					int y = static_cast<int>((i - x)/width);
					sf::Vector2i pos(x, y);
					this->tiles.at(i) = Tile(pos, tiles.at(i)); // this->tiles not to be confused with tiles :D
				}
				break;
			}
		}
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

void Board::moveTile(sf::Vector2i pos, sf::Vector2i newPos)
{
	// if the tile is not already at newPos
	if (pos != newPos)
	{
		// move the tile at pos to the tile at newPos and set the tile at pos to empty
		getTile(newPos).number = getTile(pos).number;
		getTile(pos).number = 0;
	}
	// if the tile is already there, do nothing
}

sf::Vector2i Board::nextTile(sf::Vector2i pos, Direction dir) const
{
	sf::Vector2i newPos = pos;
	switch (dir)
	{
	case Direction::Left:
		// check to the left of the last tile checked starting to the left of pos
		newPos.x -= 1;
		while (true)
		{
			if (newPos.x < 0) // newPos.x = -1 (next 'tile' is a wall
			{
				break;
			}
			// check separately because walls arent in Board::tiles
			else if (tiles.at(newPos.x + width * newPos.y).number != 0)
			{
				break;
			}
			else newPos.x -= 1; // check further left
		}
		// ^^ if newPos is to the left of the first column (if x = -1) or the tile at newPos is occupied
		// it will break
		break;
	case Direction::Right:
		// check to the right of the last tile checked starting to the right of pos
		newPos.x += 1;
		while (true)
		{
			if (newPos.x == width) // newPos.x = width (next 'tile' is a wall)
			{
				break;
			}
			// check separately because walls arent in Board::tiles
			else if (tiles.at(newPos.x + width * newPos.y).number != 0)
			{
				break;
			}
			else newPos.x += 1; // check further right
		}
		// ^^ if newPos is to the right of the last column (if x = width) or the tile at newPos is occupied
		// it will break
		break;
	case Direction::Up:
		// check above the last tile checked starting 1 above pos
		newPos.y -= 1;
		while (true)
		{
			if (newPos.y < 0) // newPos.y = -1 (next 'tile' is a wall)
			{
				break;
			}
			// check separately because walls arent in Board::tiles
			else if (tiles.at(newPos.x + width * newPos.y).number != 0)
			{
				break;
			}
			else newPos.y -= 1; // check further below
		}
		// ^^ if newPos is above the first row (if y = -1) or the tile at newPos is occupied
		// it will break
		break;
	case Direction::Down:
		// check below the last tile checked starting 1 below pos
		newPos.y += 1;
		while (true)
		{
			if (newPos.y == height) // newPos.y = height (next 'tile' is a wall)
			{
				break;
			}
			// check separately because walls arent in Board::tiles
			else if (tiles.at(newPos.x + width * newPos.y).number != 0)
			{
				break;
			}
			else newPos.y += 1; // check further below
		}
		// ^^ if newPos is below the last row (if y = height) or the tile at newPos is occupied
		// it will break
		break;
	}
	return newPos; // the position of the next tile or wall in direction dir
}
