#include "Board.h"
#include <utility>
#include "Menu.h"

class Game
{
public:
	Game(float w, float h, sf::RenderWindow& wnd);
	Game() = delete;
	~Game() = default;
	void run(sf::RenderWindow& wnd);
	void events(sf::RenderWindow& wnd); // event loop
	void update(sf::RenderWindow& wnd); // game logic
	void draw(sf::RenderWindow& wnd); // drawing
private:
	void checkMoves();
private:
	float width;
	float height;
	Board board;
	Menu menu;
	// determines if the game has started. 
	// inProgress.second is one of these:
	// 1) if first is false then second is ""
	// 2) if first is true then second can be "new" for a new game
	// 3) or the name of a loaded game (when that is implemented)
	std::pair<bool,std::string> inProgress; 
	std::vector<std::pair<Direction, bool>> canMove;
};
