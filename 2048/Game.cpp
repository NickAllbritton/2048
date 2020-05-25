#include "Game.h"



Game::Game(float width, float height) : width(width), height(height), board(4,4, width, height) {}

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
				board.move(Direction::Left);
				break;
			case sf::Keyboard::Key::Right:
				board.move(Direction::Right);
				break;
			case sf::Keyboard::Key::Up:
				board.move(Direction::Up);
				break;
			case sf::Keyboard::Key::Down:
				board.move(Direction::Down);
				break;
			}
			}
		}
	}
}

void Game::update(sf::RenderWindow& wnd)
{
	// process game logic
}

void Game::draw(sf::RenderWindow& wnd)
{
	// draw objects
	board.draw(wnd);
}