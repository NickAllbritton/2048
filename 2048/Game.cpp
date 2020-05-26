#include "Game.h"

Game::Game(float width, float height) 
	:
	width(width), height(height),
	board(4,4, width, height),
	canMove(4)
{
	for (size_t i = 0; i < canMove.size(); i++)
	{
		canMove.at(i).first = static_cast<Direction>(i);
		canMove.at(i).second = true;
	}
}

void Game::run(sf::RenderWindow& wnd)
{
	// handle events
	events(wnd);

	wnd.clear(sf::Color(230, 230, 225));
	update(wnd); // game logic
	draw(wnd); // draw
	wnd.display();
}

void Game::events(sf::RenderWindow& wnd)
{
	sf::Event event;
	while (wnd.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			wnd.close();
			break;
		case sf::Event::KeyPressed:
			{
			switch (event.key.code)
			{
			case sf::Keyboard::Key::Left:
				board.move(Direction::Left, canMove);
				break;
			case sf::Keyboard::Key::Right:
				board.move(Direction::Right, canMove);
				break;
			case sf::Keyboard::Key::Up:
				board.move(Direction::Up, canMove);
				break;
			case sf::Keyboard::Key::Down:
				board.move(Direction::Down, canMove);
				break;
			}
			}
		}
	}
}

void Game::update(sf::RenderWindow& wnd)
{
	// limit what moves are valid
	checkMoves();
}

void Game::draw(sf::RenderWindow& wnd)
{
	// draw objects
	board.draw(wnd);
}

void Game::checkMoves()
{
	for (auto& direction : canMove)
	{
		direction.second = false;
	}
	// movement is assumed false unless there is a valid move
	for (sf::Vector2i pos(0, 0); pos.x < board.getWidth(); pos.x++)
	{
		for (pos.y = 0; pos.y < board.getHeight(); pos.y++)
		{
			// if any (occupied!) tiles are available to move in any given direction
			// that direction is a possible move
			if (board.getTile(pos).number != 0)
			{
				if (board.nextTileAvailable(pos, Direction::Left))
				{
					canMove.at(static_cast<int>(Direction::Left)).second = true;
				}
				if (board.nextTileAvailable(pos, Direction::Right))
				{
					canMove.at(static_cast<int>(Direction::Right)).second = true;
				}
				if (board.nextTileAvailable(pos, Direction::Up))
				{
					canMove.at(static_cast<int>(Direction::Up)).second = true;
				}
				if (board.nextTileAvailable(pos, Direction::Down))
				{
					canMove.at(static_cast<int>(Direction::Down)).second = true;
				}
			}
		}
	}
}
