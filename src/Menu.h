#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
public:
	Menu(sf::RenderWindow& wnd);
	~Menu() = default;

private:
	// vector of menu options
	std::vector<std::string> options;
	bool startGame = false;
};
