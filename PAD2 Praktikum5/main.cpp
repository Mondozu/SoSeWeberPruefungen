//Sebastian Sudan Mendoza (764918), David Knebel (765319), Daniel Frey (765015), Kian Khederzadeh(764921)
#include<iostream>
using namespace std;

#include"Season.h"

int main() {
	setlocale(LC_ALL, "");
	string tmp, epNr, nameGer, nameEng, content;
	int userInput;

	Season season1;

	fstream inFileStream("Lost_Staffel_1.txt", ios::in);
	getline(inFileStream, tmp);

	while (getline(inFileStream, tmp, ' ')) {

		getline(inFileStream, epNr, '\n');
		getline(inFileStream, nameGer, '(');
		getline(inFileStream, nameEng, ')');
		getline(inFileStream, tmp, '\n');
		getline(inFileStream, content, '*');

		Episode tempEP{ epNr, nameGer, nameEng, content };
		season1.push_backEpisode(tempEP);
	}


	do {
		cout
			<< "[1] Englische Episodentitel beliebiger Episode ausgeben" << endl
			<< "[2] Nur Rückblicke einer beliebigen Episode ausgeben" << endl
			<< "[3] Die 15 häufigsten Wörter der Rückblicke einer Episode ausgeben" << endl
			<< "[4] Hauptpersonen aller Episoden ausgeben" << endl << endl
			<< "[9] Beenden" << endl
			<< "Ihre Wahl: ";
		cin >> userInput;

		switch (userInput) {
		case 1:
			cout << "**** Inhalt einer Episode ausgeben ****" << endl;
			cout << season1.printAllEpisodes();
			cout << "Welche Episode soll ausgegeben werden?: ";
			cin >> epNr;

			if (season1.episodeExists(epNr)) {
				cout << season1.printEpisode(epNr);
			}
			else { cout << "Episode existiert nicht" << endl; }
			break;

		case 2:
			cout << "**** Nur Rückblicke einer Episode ausgeben ****" << endl;
			cout << "Von welchen Episoden sollen die Rückblicke ausgegeben werden?: ";
			cin >> epNr;
			cout << endl;
			if (season1.episodeExists(epNr)) {
				cout << season1.printFlashbacks(epNr);
			}
			else { cout << "Episode existiert nicht" << endl; }
			break;

		case 3:
			cout << "**** Die 15 häufigsten Wörter ausgeben ****" << endl;
			cout << "Von welcher Episode sollen die häufigsten Wörter ausgegeben werden?: ";
			cin >> epNr;
			cout << endl;
			if (season1.episodeExists(epNr)) {
				cout << season1.printMostUsedWords(epNr);
			}
			else { cout << "Episode existiert nicht" << endl; }
			break;

		case 4:
			cout << "**** Hauptpersonen aller Episoden ausgeben ****" << endl;
			cout << season1.printMainCharacters() << endl;
			break;

		case 9: break;
		default:
			cout << "Ungültige Eingabe" << endl;
			break;
		}
	} while (userInput != 9);

}