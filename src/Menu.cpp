#include "Menu.h"

Menu::Menu(sf::RenderWindow& wnd)
{
	this->options = {
		std::string("New game"),
		// load game -- implement later
		std::string("High scores"),
		std::string("Credits")
		};	
}
