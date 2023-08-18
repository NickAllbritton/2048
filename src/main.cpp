#include "Game.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes().at(0), "2048", sf::Style::Fullscreen);
	window.setKeyRepeatEnabled(false); // only one key event per key press
	Game game(window.getSize().x, window.getSize().y, window);
	// program and game loop
	while (window.isOpen()) game.run(window);

	return 0;
}
