//Sebastian Sudan Mendoza (764918), David Knebel (765319), Daniel Frey (765015), Kian Khederzadeh(764921)
#pragma once
#include"Episode.h"

#include<iomanip>
#include<map>
#include<algorithm>
#include<fstream>


class Season {
public:
	void push_backEpisode(const Episode&);
	bool episodeExists(const std::string&);
	int getEPindex(const std::string&);
	std::string printAllEpisodes();
	std::string printEpisode(const std::string&);
	std::string printFlashbacks(const std::string&);
	std::string printMostUsedWords(const std::string&);
	std::string printMainCharacters();

private:
	std::vector<std::pair<std::string, Episode>>episodes;
};