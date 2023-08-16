#include "Menu.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

Menu::Menu(sf::Vector2u winSize)
	:
	padding(20.f),highlighted(MenuOption::NewGame),rects(25)
{

	font.loadFromFile("../resources/ONEDAY.ttf");

	// draw the decorative squares

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<int> width(static_cast<int>(winSize.x*1/8), static_cast<int>(winSize.x*7/8));
	std::uniform_int_distribution<int> height(static_cast<int>(winSize.y*1/8), static_cast<int>(winSize.y*7/8));
	std::uniform_int_distribution<int> sideLen(3, static_cast<int>(winSize.x/8));
	std::uniform_int_distribution<int> shade(52, 100);

	std::vector<sf::Vector2f> pos(50); // positions of all 50  squares
	std::vector<float> size(50); // side length of all 50 squares
	for(size_t i = 0; i < rects.size(); i++)
	{
		size.at(i) = static_cast<float>(sideLen(rng)); // random side length for each square
		pos.at(i) = sf::Vector2f(static_cast<float>(width(rng)), static_cast<float>(height(rng))); // random position within the window for each sqr
		do
		{
			for(size_t j = 0; j < i; j++)
			{
				// detect a collision
				if(((pos.at(i).x < pos.at(j).x + size.at(j)) && (pos.at(i).x > pos.at(j).x))
				|| ((pos.at(i).x + size.at(i) > pos.at(j).x) && (pos.at(i).x + size.at(i) < pos.at(j).x + size.at(j)))
				|| ((pos.at(i).y < pos.at(j).y + size.at(j)) && (pos.at(i).y > pos.at(j).y))
				|| ((pos.at(i).y + size.at(i) > pos.at(j).y) && (pos.at(i).y + size.at(i) < pos.at(j).y + size.at(j))))
				{
					size.at(i) = static_cast<float>(sideLen(rng)); // assign new size
					pos.at(i) = sf::Vector2f(static_cast<float>(width(rng)), static_cast<float>(height(rng))); // new position
					j = 0; // restart loop
				}
			}
			break; // if this line is reached square at i does not collide with any other square so break from the do while loop
		} while(true);
		rects.at(i) = sf::RectangleShape(sf::Vector2f(static_cast<float>(size.at(i)), static_cast<float>(size.at(i))));
		int randShade = shade(rng);
		rects.at(i).setPosition(pos.at(i));
		rects.at(i).setFillColor(sf::Color(randShade, randShade, randShade)); // random shade of gray
	}

	// menu options

	options = {
		std::string("New game"),
		std::string("Load game"),
		std::string("High scores"),
		std::string("Credits")
		};
	

	// Start drawing the menu
	title.setFont(font);
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
		optList.at(i).setFont(font);
		optList.at(i).setCharacterSize(50.f);
		optList.at(i).setFillColor(sf::Color(18, 188, 148));
		optList.at(i).setString(options.at(i)); // menu option string
		// text is aligned with the left side of the title text
		// take the bottom of the title text and add padding*(i+3) give the right amount of padding
		// from that add option text's height times i which accounts for the height of all option texts printed above it
		optList.at(i).setPosition(sf::Vector2f(title.getPosition().x, 
					 title.getPosition().y + title.getLocalBounds().height + padding*(i+3) + optList.at(i).getLocalBounds().height*i));
	}
	
	savedGames = readSavedGames("../resources/saved_games.xml");

	// load game menu
	loadMenu.inThisMenu = false;

	loadMenu.title.setString("Load Game");
	loadMenu.title.setFont(font);
	loadMenu.title.setCharacterSize(60.f);
	loadMenu.title.setFillColor(sf::Color(18, 188, 148));
	loadMenu.title.setPosition(sf::Vector2f(winSize.x / 2.f - loadMenu.title.getLocalBounds().width / 2, 40.f));
	loadMenu.options = std::vector<sf::Text>(savedGames.size()); // create enough options for each saved game
	int i = 0;
	for(auto& game : savedGames)
	{
		// set all the text objects' strings for each saved game
		loadMenu.options.at(i).setString(game.name + std::string("  --  ") + game.player
					+ std::string("  (") + std::to_string(game.score) + std::string(")"));
		// set the initial color of each object and the font size
		loadMenu.options.at(i).setFont(font);
		loadMenu.options.at(i).setCharacterSize(30.f);
		loadMenu.options.at(i).setFillColor(sf::Color(18, 188, 148));
		loadMenu.options.at(i).setPosition(sf::Vector2f(loadMenu.title.getPosition().x, 
				loadMenu.title.getPosition().y + loadMenu.title.getLocalBounds().height + 
				loadMenu.options.at(i).getLocalBounds().height*i + (i+2)*20.f));
		i++;
	}
}


void Menu::draw(sf::RenderWindow& wnd)
{
	// change the look of the highlighted menu option
	// and change all of the other menu options back to the default
	for(size_t i = 0; i < optList.size(); i++)
	{
		if(i == static_cast<int>(highlighted)) optList.at(i).setFillColor(sf::Color(195, 0, 127));
		else optList.at(i).setFillColor(sf::Color(18, 188, 148));
	}

	// draw the decorative squares
	for(auto& square : rects)
	{
		wnd.draw(square);
	}

	// draw the menu
	wnd.draw(title);
	for(auto& opt : optList)
	{
		wnd.draw(opt);
	}
}

void Menu::drawLoadGame(sf::RenderWindow& wnd)
{
	// set the color of the options correctly pink if highlighted
	for(size_t i = 0; i < loadMenu.options.size(); i++)
	{
		if(i == loadMenu.highlighted) loadMenu.options.at(i).setFillColor(sf::Color(195, 0, 127));
		else loadMenu.options.at(i).setFillColor(sf::Color(18, 188, 148));
	}

	for(auto& opt : loadMenu.options)
	{
		wnd.draw(opt);
	}

	wnd.draw(loadMenu.title);
}

std::vector<SavedGame> Menu::readSavedGames(std::string file)
{
	// parse the xml file "file" and store the saved game data in a vector of Menu::SavedGame objects
	std::vector<SavedGame> SavedGames;
	
	pt::ptree saved_gameXML;
	pt::read_xml(file, saved_gameXML);

	// get all the children of the root node <Games>
	for(auto& game : saved_gameXML.get_child("Games"))
	{
		SavedGame loadedGame;
		loadedGame.name = game.second.get<std::string>("name");
		loadedGame.player = game.second.get<std::string>("player");
		loadedGame.score = game.second.get<int>("score");
		// lastly load the tiles of the the saved game
		std::vector<int> tiles;
		for(auto& tile : game.second.get_child("tiles"))
		{
			tiles.push_back(std::stoi(tile.second.data()));
		}
		SavedGames.push_back(loadedGame);
	}

	return SavedGames;
}
