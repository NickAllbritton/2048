#pragma once
#include "Board.h"


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
};