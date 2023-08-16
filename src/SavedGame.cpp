#include "SavedGame.h"

std::vector<SavedGame> readSavedGames(std::string file)
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
		loadedGame.tiles = tiles;
		SavedGames.push_back(loadedGame);
	}

	return SavedGames;
}
