#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

enum class MenuOption
{
	NewGame,
	LoadGame,
	HighScores,
	Credits
};

class Menu
{
public:
	Menu(sf::Vector2u winSize);
	~Menu() = default;
	void draw(sf::RenderWindow& wnd);
public:
	MenuOption highlighted;	
private:
	sf::Font oneday;
	std::vector<std::string> options;
	std::vector<sf::Text> optList;
	std::vector<sf::RectangleShape> rects;
	sf::Text title;
	float padding;
};
