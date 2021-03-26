#pragma once
#include<string>
#include<vector>
#include<map>
#include<sstream>
#include<iomanip>
#include<fstream>


class Episode {
public:
	Episode() {}
	Episode(const std::string&, const std::string&, const std::string&, const std::string&);

	std::string getEpNr()const;
	std::string getTitleGer()const;
	std::string getTitleEng()const;
	std::string getContent()const;

	std::string getFlashbacks()const;
	std::string get15MostUsedWords()const;
	std::string getMainCharacters()const;
private:
	std::string epNr;
	std::string nameGer;
	std::string nameEng;

	std::string content;

	std::vector<std::string>flashbacks;
};