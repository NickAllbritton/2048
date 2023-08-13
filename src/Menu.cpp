#include "Menu.h"

Menu::Menu(sf::Vector2u winSize)
	:
	padding(20.f)
{
	options = {
		std::string("New game"),
		std::string("Load game"),
		std::string("High scores"),
		std::string("Credits")
		};
	

	// Start drawing the menu
	oneday.loadFromFile("../resources/ONEDAY.ttf");


	title.setFont(oneday);
	title.setCharacterSize(120.f);
	title.setFillColor(sf::Color(18, 188, 148));
	title.setString("2048");
	// for the x:
	// divide the window width in half and subtract half the length of the title
	// for the y:
	// hardcoded for now... TODO: change the y to a dynamic value
	title.setPosition(sf::Vector2f(winSize.x / 2.f - title.getLocalBounds().width / 2.f, 40.f));

	// initialize optList to have the same size as options, naturally
	optList = std::vector<sf::Text>(static_cast<int>(options.size()));

	// menu options settings
	for(size_t i = 0; i < options.size(); i++)
	{
		optList.at(i).setFont(oneday);
		optList.at(i).setCharacterSize(50.f);
		optList.at(i).setFillColor(sf::Color(18, 188, 148));
		optList.at(i).setString(options.at(i)); // menu option string
		// text is aligned with the left side of the title text
		// take the bottom of the title text and add padding*(i+3) give the right amount of padding
		// from that add option text's height times i which accounts for the height of all option texts printed above it
		optList.at(i).setPosition(sf::Vector2f(title.getPosition().x, 
					 title.getPosition().y + title.getLocalBounds().height + padding*(i+3) + optList.at(i).getLocalBounds().height*i));
	}
}


void Menu::draw(sf::RenderWindow& wnd)
{
	wnd.draw(title);
	for(auto& opt : optList)
	{
		wnd.draw(opt);
	}
}
