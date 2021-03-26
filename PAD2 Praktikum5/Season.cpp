//Sebastian Sudan Mendoza (764918), David Knebel (765319), Daniel Frey (765015), Kian Khederzadeh(764921)
#include"Season.h"


void Season::push_backEpisode(const Episode& inEpisode) {
	episodes.push_back(std::make_pair(inEpisode.getEpisodeNr(), inEpisode));
}



bool Season::episodeExists(const std::string& searchingForEP) {
	for (size_t i = 0; i < episodes.size(); i++) {
		if (episodes[i].first == searchingForEP) {
			return true;
		}
	}
	return false;
}



int Season::getEPindex(const std::string& epNrString) {
	for (size_t i = 0; i < episodes.size(); i++) {
		if (episodes[i].first == epNrString) {
			return i;
		}
	}
	return -1; //Wird nicht vorkommen, da immer mit episodeExists überprüft wird ob die EP existiert.
}



std::string Season::printAllEpisodes() {
	std::stringstream outStream;

	for (size_t i = 0; i < episodes.size(); i++) {
		outStream << std::left << std::setw(7) << episodes[i].first << std::setw(20) << episodes[i].second.getNameEnglisch() << std::endl;
	}
	outStream << std::endl;

	return outStream.str();
}



std::string Season::printEpisode(const std::string& inEPnr) {
	std::stringstream outStream;
	int index{ getEPindex(inEPnr) };
	outStream << "Episode " << episodes[index].first << std::endl;
	outStream << "Ger: " << episodes[index].second.getNameEnglisch() << std::endl;
	outStream << "Eng; " << episodes[index].second.getNameGerman() << std::endl;
	outStream << "Inhalt: " << std::endl << episodes[index].second.getEpisodeContent() << std::endl << std::endl;

	return outStream.str();
}



std::string Season::printFlashbacks(const std::string& inEPnr) {
	int index{ getEPindex(inEPnr) };
	return episodes[index].second.getFlashbacks();
}



std::string Season::printMostUsedWords(const std::string& inEPnr) {
	std::stringstream sstream, outStream;
	int index{ getEPindex(inEPnr) };
	std::string word;
	std::map<std::string, int>wordCountMap;
	std::vector<std::pair<std::string, int>>wordCountPairs;

	sstream << episodes[index].second.getFlashbacks();//Liest alle Wörter der Flashbacks in eine sortierte map
	while ((sstream >> word).good()) {
		wordCountMap.emplace(word, wordCountMap[word]++);
	}

	int j{ 0 };
	for (auto itr = wordCountMap.begin(); itr != wordCountMap.end(); itr++, j++) { //Iteriert durch die map und überträgt die Werte in den Vector mir Pairs.
		wordCountPairs.push_back(std::make_pair(itr->first, itr->second));
	}

	std::sort(wordCountPairs.rbegin(), wordCountPairs.rend(),
		[](const auto& a, const auto& b) {return a.second < b.second;
		});

	for (int i = 0; i < 15; i++) { //Gibt die ersten 15 aus
		outStream << std::setfill('.') << std::left << std::setw(15) << wordCountPairs[i].first << wordCountPairs[i].second << std::endl;
	}
	return outStream.str();
}



std::string Season::printMainCharacters() {
	std::stringstream outStream;
	outStream << std::left << std::setw(10) << "Episode" << std::setw(23) << "Titel: " << "Hauptpersonen:" << std::endl;
	std::vector<std::string>mainCharacters;
	std::string word, tmp;

	std::fstream charFile("Hauptpersonen.txt", std::ios::in);
	while ((charFile >> word).good()) {
		mainCharacters.push_back(word);
	}

	for (size_t k = 0; k < episodes.size(); k++) { //Für jede Episode...
		std::vector<int>mainCharacterMentions(mainCharacters.size(), 0);
		std::stringstream flashbackText{ episodes[k].second.getFlashbacks() };


		while ((flashbackText >> word).good()) {
			tmp = word.substr(0, word.size() - 1); //Für den Fall das hinter dem Namen ein Punkt oder Komma ist. Leider würde die (Regen-)"Jacke" dann auch dem guten "Jack" zugeschrieben werden.
			for (size_t i = 0; i < mainCharacters.size(); i++) {
				if ((word == mainCharacters[i]) || tmp == mainCharacters[i]) {
					mainCharacterMentions[i]++;
				}
			}
		}

		int amountOfMainCharacters{ 0 };
		for (size_t i = 0; i < mainCharacterMentions.size(); i++) {
			if ((mainCharacterMentions[i] > 4)) {
				amountOfMainCharacters++;
				mainCharacterMentions[i] = 1;
			}
			else {
				mainCharacterMentions[i] = 0;
			}
		}
		//Am Ende bleibt so ein Vector mit 0en und 1en. 0 für keine Hautptperson und 1 für Hauptperson die min. 5 mal erwähnt wurde. 


		switch (amountOfMainCharacters) { //Ausgabe je nach Anzahl an Hauptpersonen
		case 0:
			outStream << std::left << std::setw(10) << episodes[k].first << std::setw(23) << episodes[k].second.getNameGerman() << "Keine spezielle" << std::endl;
			break;

		case 1:
			outStream << std::left << std::setw(10) << episodes[k].first << std::setw(23) << episodes[k].second.getNameGerman();
			for (size_t i = 0; i < mainCharacterMentions.size(); i++) {
				if (mainCharacterMentions[i] == 1) {
					outStream << mainCharacters[i] << std::endl;
				}
			}
			break;

		default:
			bool firstname = true;
			outStream << std::left << std::setw(10) << episodes[k].first << std::setw(23) << episodes[k].second.getNameGerman();
			for (size_t i = 0; i < mainCharacterMentions.size(); i++) {
				if ((mainCharacterMentions[i] == 1) && (firstname == true)) {
					outStream << mainCharacters[i];
					firstname = false;
				}
				else if ((mainCharacterMentions[i] == 1) && (firstname == false)) {
					outStream << ", " << mainCharacters[i];
				}
			}
			outStream << std::endl;
			break;
		}

	}

	return outStream.str();
}