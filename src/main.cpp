#include "Game.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "2048");
	window.setKeyRepeatEnabled(false); // only one key event per key press
	Game game(window.getSize().x, window.getSize().y);
	// program and game loop
	while (window.isOpen()) game.run(window);

	return 0;
}
