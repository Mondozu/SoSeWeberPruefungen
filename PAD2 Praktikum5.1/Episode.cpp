#include"Episode.h"

Episode::Episode(const std::string& inEpNr, const std::string& inNameGer, const std::string& inNameEng, const std::string& inContent)
	:epNr(inEpNr), nameGer(inNameGer), nameEng(inNameEng), content(inContent)
{
	size_t startPos{ 0 }, offset{ 0 };

	while ((startPos = inContent.find("<FLASHBACK>", offset)) != std::string::npos) {
		offset = inContent.find("</FLASHBACK>", startPos);
		flashbacks.push_back(inContent.substr((startPos + 12), offset - (startPos + 13)));
	}
}

std::string Episode::getEpNr()const { return epNr; }
std::string Episode::getTitleGer()const { return nameGer; }
std::string Episode::getTitleEng()const { return nameEng; }
std::string Episode::getContent()const { return content; }

std::string Episode::getFlashbacks()const {
	std::stringstream outStream;
	for (const std::string& x : flashbacks) {
		outStream << x << std::endl << std::endl;
	}
	return outStream.str();
}

std::string Episode::get15MostUsedWords()const {
	std::string word;
	std::stringstream wordStream, outStream;
	std::map < std::string, int>wordCountMap;

	wordStream << this->getFlashbacks();

	while ((wordStream >> word).good()) {
		wordCountMap.emplace(word, wordCountMap[word]++);
	}

	std::multimap<int, std::string>sortedWords;
	std::multimap<int, std::string>::reverse_iterator rItr = sortedWords.rbegin();
	for (const auto& x : wordCountMap) {
		sortedWords.emplace(x.second, x.first);
	}

	for (size_t i = 0; i < 14; i++) {
		outStream << std::left << std::setw(5) << rItr->first << rItr->second << std::endl;
		rItr++;
	}

	return outStream.str();
}

std::string Episode::getMainCharacters()const {
	std::stringstream outStream;
	std::ifstream mainCharactersFile("Hauptpersonen.txt", std::ios::in);
	std::map<std::string, int>mainCharacterCounter;
	std::string flashbackText{ getFlashbacks() }, word;

	while ((mainCharactersFile >> word).good()) {
		mainCharacterCounter.emplace(word, 0);
	}

	for (auto& x : mainCharacterCounter) {
		size_t startPos{ 0 }, offset{ 0 };

		while ((startPos = flashbackText.find(x.first, offset)) != std::string::npos) {
			offset = startPos + x.first.size();
			x.second++;
		}
	}

	std::vector<std::string>mainCharacters;
	for (const auto& x : mainCharacterCounter) {
		if (x.second > 4) {
			mainCharacters.push_back(x.first);
		}
	}

	bool first = true;
	if (mainCharacters.size() == 0) {
		return "Keine Spezielle";
	}
	else {
		for (size_t i = 0; i < mainCharacters.size(); i++) {
			if (first) {
				outStream << mainCharacters[i];
				first = false;
			}
			else {
				outStream << ", " << mainCharacters[i];
			}
		}
	}
	return outStream.str();
}