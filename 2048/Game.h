#pragma once
#include "Board.h"

typedef sf::Keyboard kbd;
typedef sf::Mouse mouse;
typedef sf::RenderWindow Window;

class Game
{
public:
	Game(float w, float h);
	Game() = delete;
	~Game() = default;
	void run(Window& wnd);
	void events(Window& wnd); // event loop
	void update(Window& wnd); // game logic
	void draw(Window& wnd); // drawing
private:
private:
	float width;
	float height;
	Board board;
};