#include <vector>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

#ifndef SavedGame_h
#define SavedGame_h

struct SavedGame
{
	std::string name;
	std::string player;
	int score;
	std::vector<int> tiles;
};

std::vector<SavedGame> readSavedGames(std::string file);

#endif
