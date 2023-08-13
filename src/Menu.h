#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
public:
	Menu(sf::Vector2u winSize);
	~Menu() = default;
	void draw(sf::RenderWindow& wnd);
private:
	sf::Font oneday;
	std::vector<std::string> options;
	std::vector<sf::Text> optList;
	sf::Text title;
	float padding;
};
