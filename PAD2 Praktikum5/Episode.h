//Sebastian Sudan Mendoza (764918), David Knebel (765319), Daniel Frey (765015), Kian Khederzadeh(764921)
#pragma once
#include<string>
#include<vector>
#include<sstream>


class Episode {
public:
	Episode();
	Episode(const std::string&, const std::string&, const std::string&, const std::string&);

	std::string getEpisodeNr() const;

	std::string getNameGerman() const;
	std::string getNameEnglisch() const;

	std::string getEpisodeContent() const;
	std::string getFlashbacks()const;

private:
	std::string episodeNr;
	std::string nameGerman;
	std::string nameEnglish;
	std::string episodeContent;

	std::vector<std::string>flashbacks;
};