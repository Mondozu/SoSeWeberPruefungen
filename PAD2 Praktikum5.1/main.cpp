#include<iostream>
#include"Episode.h"
using std::endl; using std::cout; using std::cin;

int main() {
	setlocale(LC_ALL, "");
	std::map<std::string, Episode>season1;
	std::map<std::string, Episode>::iterator mapItr;
	std::string dummy, epNr, nameGer, nameEng, content, userInput;
	int menuSelection{ 0 };
	std::ifstream inScript("Lost_Staffel_1.txt", std::ios::in);
	if (!inScript) {
		std::cerr << "Fehler beim Öffnen";
		exit(EXIT_FAILURE);
	}
	std::getline(inScript, dummy);
	while (std::getline(inScript, dummy, ' ')) { //Liest die letzten "***\nEPISODE" ein
		std::getline(inScript, epNr, '\n');
		std::getline(inScript, nameGer, '(');
		std::getline(inScript, nameEng, ')');
		std::getline(inScript, dummy, '\n');
		std::getline(inScript, content, '*');
		Episode tempEP{ epNr,nameGer,nameEng,content };
		season1.emplace(epNr, tempEP);
	}
	inScript.close();

	do {
		cout << "[1] Englische Episodentitel und Inhalt einer beliebigen Episode ausgeben" << endl
			<< "[2] Nur Rückblicke einer beliebigen Episode ausgeben" << endl
			<< "[3] Die 15 häufigsten Wörter der Rückblicke einer Episode ausgeben" << endl
			<< "[4] Hauptpersonen aller Episoden ausgeben" << endl << endl
			<< "[9] Programm beenden" << endl
			<< "Ihre Wahl: ";
		cin >> menuSelection;

		switch (menuSelection) {
		case 1:
			for (const auto& x : season1) {
				cout << x.first << " - " << x.second.getTitleEng() << endl;
			}
			cout << "Der Inhalt welcher Episode soll augegeben werden?: ";
			cin >> userInput;
			mapItr = season1.find(userInput);
			if (mapItr != season1.end()) {
				//if (season1.find(userInput) != season1.end()) {
				cout << mapItr->second.getContent() << endl;
			}
			else {
				cout << "Episode nicht gefunden." << endl;
			}
			break;
		case 2:
			cout << "Die Rückblicke welcher Episode sollen augegeben werden?: ";
			cin >> userInput;
			mapItr = season1.find(userInput);
			if (mapItr != season1.end()) {
				//if (season1.find(userInput) != season1.end()) {
				cout << mapItr->second.getFlashbacks() << endl;
			}
			else {
				cout << "Episode nicht gefunden." << endl;
			}
			break;
		case 3:
			cout << "Von welcher Episode sollen die 15 häufigsten Wörter augegeben werden?: ";
			cin >> userInput;
			mapItr = season1.find(userInput);
			if (mapItr != season1.end()) {
				//if (season1.find(userInput) != season1.end()) {
				cout << mapItr->second.get15MostUsedWords() << endl;
			}
			else {
				cout << "Episode nicht gefunden." << endl;
			}
			break;
		case 4:
			cout << "Hauptfiguren aller Episoden ausgeben"<<endl;
			for (const auto& x : season1) {
				cout <<std::left<<std::setw(5)<< x.first << x.second.getMainCharacters() << endl;
			}
		case 9: break;
		default:
			cout << "Ungültige Eingabe" << endl;
			break;
		}
	} while (menuSelection != 9);
}