#include "Tile.h"
#include <random>

enum class Direction
{
	Left,
	Right,
	Up,
	Down
};

class Board
{
public:
	// default constructor must be available so that the board is not created until
	// after you have exited the menu
	Board() = default;
	Board(int x, int y, float width, float height, std::string name);
	~Board() = default;
	Tile& getTile(sf::Vector2i pos);
	int getWidth() const
	{
		return width;
	}
	int getHeight() const
	{
		return height;
	}
	void draw(sf::RenderWindow& wnd);
	void move(Direction dir, std::vector<std::pair<Direction, bool>> canMove);
	bool nextTileAvailable(sf::Vector2i pos, Direction dir);
	bool contains(sf::Vector2i pos)
	{
		return pos.x >= 0 && pos.y >= 0 && pos.x < width && pos.y < height; // verify that this position is valid
		// maybe later write a function to determine if a pos is a wall and use that to move() more readable
	}
private:
	void drawCell(sf::RenderWindow& wnd, Tile& tile);
	void spawnInitialTiles();
	void spawnTile(Direction dir);
	void moveTile(sf::Vector2i pos, sf::Vector2i newPos);
	sf::Vector2i nextTile(sf::Vector2i pos, Direction dir) const;
private:
	static constexpr float tileLen = 115.f;
	int width;
	int height;
	std::string name;
	sf::RectangleShape backgroundRect;
	std::vector<Tile> tiles;
	std::uniform_real_distribution<float> newTileProb;
};
