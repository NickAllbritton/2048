#include "Game.h"

Game::Game(float width, float height, sf::RenderWindow& wnd) 
	:
	width(width), height(height),
	menu(wnd.getSize()),
	inProgress(false, ""), canMove(4)
{
	// canMove is initialized by size but all of the elements are empty
	// below it is initialized as true for every direction
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

	wnd.clear(sf::Color(32, 27, 32));

	// Select what scene to draw

	// if a game is in progress draw the board
	if(inProgress.first) draw(wnd);
	// otherwise draw the menu
	else menu.draw(wnd);

	update(wnd); // game (or menu) logic
	wnd.display();
}

void Game::events(sf::RenderWindow& wnd)
{
	// TODO: handle resize event by updating width and height
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
			if(!inProgress.first) // if player is in the menu
			{
				switch(event.key.code)
				{
				case sf::Keyboard::Key::Up:
					menu.highlighted = (static_cast<int>(menu.highlighted) == 0) 
								? 
								MenuOption::NewGame : static_cast<MenuOption>(static_cast<int>(menu.highlighted) - 1);
					break;
				case sf::Keyboard::Key::Down:
					menu.highlighted = (static_cast<int>(menu.highlighted) == 3) 
								? 
								MenuOption::Credits : static_cast<MenuOption>(static_cast<int>(menu.highlighted) + 1);
					break;
				case sf::Keyboard::Key::Enter:
					switch(menu.highlighted)
					{
					case MenuOption::NewGame:
						startGame("new");
						break;
					case MenuOption::LoadGame:
						// enter a load game menu
						// TODO: create a load game menu
						break;
					}
					break;
				}
			}
			else // then player is in a game, so handle game events
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
				// functions
				case sf::Keyboard::Key::S:
					// save current game
					break;
				}
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
		for (; pos.y < board.getHeight(); pos.y++)
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

void Game::startGame(char* name)
{
	inProgress.first = true;
	inProgress.second = name;
	board = Board(4, 4, width, height, inProgress.second); // load the board
}
