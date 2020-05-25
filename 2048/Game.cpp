#include "Game.h"

Game::Game(float width, float height) : width(width), height(height), board(4,4, width, height) {}

void Game::run(Window& wnd)
{
	// handle events
	events(wnd);

	wnd.clear(sf::Color(230, 230, 225));
	update(wnd); // game logic
	draw(wnd); // draw
	wnd.display();
}

void Game::events(Window& wnd)
{
	sf::Event event;
	while (wnd.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			wnd.close();
			break;
		}
	}
}

void Game::update(Window& wnd)
{
	// process game logic
}

void Game::draw(Window& wnd)
{
	// draw objects
	board.draw(wnd);
}