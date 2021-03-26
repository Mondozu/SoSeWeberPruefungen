//Sebastian Sudan Mendoza (764918), David Knebel (765319), Daniel Frey (765015), Kian Khederzadeh(764921)
#include"Episode.h"


Episode::Episode(const std::string& inEPnr, const std::string& inNameGer, const std::string& inNameEng, const std::string& inContent)
	:episodeNr(inEPnr), nameGerman(inNameGer), nameEnglish(inNameEng), episodeContent(inContent)
{
	//Episode nach Flashbacks durchsuchen

	size_t startPos{ 0 };
	size_t endPos{ 0 };

	while ((startPos = inContent.find("<FLASHBACK>", endPos)) != std::string::npos) {
		endPos = inContent.find("</FLASHBACK>", startPos);
		flashbacks.push_back(inContent.substr(startPos + 12, endPos - startPos - 12));
	}

}

std::string Episode::getEpisodeNr() const {
	return episodeNr;
}


std::string Episode::getNameGerman() const {
	return nameGerman;
}
std::string Episode::getNameEnglisch() const {
	return nameEnglish;
}


std::string Episode::getEpisodeContent() const {
	return episodeContent;
}

std::string Episode::getFlashbacks()const {
	std::stringstream outStream;

	for (size_t i = 0; i < flashbacks.size(); i++) {
		outStream << flashbacks[i] << std::endl << std::endl;
	}

	return outStream.str();
}