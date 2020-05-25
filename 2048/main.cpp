#include "Game.h"


int main()
{
	Window window(sf::VideoMode(800, 600), "2048");
	Game game(window.getSize().x, window.getSize().y);
	// program and game loop
	while (window.isOpen()) game.run(window);

	return 0;
}