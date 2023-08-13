#include "Menu.h"

void Menu::draw(sf::RenderWindow& wnd)
{
	options = {
		std::string("New game"),
		// load game -- implement later
		std::string("High scores"),
		std::string("Credits")
		};

	// Start drawing the menu
	sf::Font oneday;
	oneday.loadFromFile("../resources/ONEDAY.ttf");

	sf::Text title;
	std::vector<sf::Text> optsList;

	title.setFont(oneday);
	title.setCharacterSize(80.f);
	title.setFillColor(sf::Color::Black);
	title.setString("2048");
	// for the x:
	// divide the window width in half and subtract half the length of the title
	// for the y:
	// hardcoded for now... TODO: change the y to a dynamic value
	title.setPosition(sf::Vector2f(wnd.getSize().x / 2.f - title.getLocalBounds().width / 2.f, 40.f));

	wnd.draw(title);
}
