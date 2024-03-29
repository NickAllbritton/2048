#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>
#include "SavedGame.h"

enum class MenuOption
{
	NewGame,
	LoadGame,
	HighScores,
	Credits
};


struct LoadGame
{
	bool inThisMenu; // set to true to enter the load game menu
	int highlighted; // index of highlighted option in options
	sf::Text title; // title of the load game menu (should be "Load Game")
	std::vector<sf::Text> options;
};


class Menu
{
public:
	public:
	Menu(sf::Vector2u winSize);
	~Menu() = default;
	void draw(sf::RenderWindow& wnd);
	void drawLoadGame(sf::RenderWindow& wnd);
public:
	MenuOption highlighted;
	sf::Font font;
	std::vector<SavedGame> savedGames;
	LoadGame loadMenu;
private:
	std::vector<std::string> options;
	std::vector<sf::Text> optList;
	std::vector<sf::RectangleShape> rects;
	sf::Text title;
	float padding;
};
