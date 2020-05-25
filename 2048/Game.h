#pragma once
#include "Board.h"
#include <utility>

class Keyboard // simple class that only all takes one keyboard input at a time
{
private:
	sf::Keyboard::Key key = sf::Keyboard::Key::Unknown; // default to unknown
public:
	void keyEvent(sf::Event e)
	{
		if (e.type == sf::Event::KeyPressed)
		{
			key = e.key.code;
		}
	}
	bool isKeyPressed(sf::Keyboard::Key k)
	{
		return key == k;
	}
};

class Game
{
public:
	Game(float w, float h);
	Game() = delete;
	~Game() = default;
	void run(sf::RenderWindow& wnd);
	void events(sf::RenderWindow& wnd); // event loop
	void update(sf::RenderWindow& wnd); // game logic
	void draw(sf::RenderWindow& wnd); // drawing
private:
private:
	float width;
	float height;
	Board board;
	Keyboard kbd;
};