#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
public:
	Menu() = default;
	~Menu() = default;
	void draw(sf::RenderWindow& wnd);
private:
	// vector of menu options
	std::vector<std::string> options;
	bool startGame = false;
};
