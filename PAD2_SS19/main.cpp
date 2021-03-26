#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <iomanip>

#include "Town.h"
using std::endl;
using std::cout;
using std::cin;

bool operator<(const Town& l, const Town& r) { return l.getStadtnamen() < r.getStadtnamen(); };

void outputToFile(std::vector<std::pair<Town, double>> container) {
	std::stringstream outStream;
	std::ofstream outFile("Growth.txt", std::ios::out);
	for (auto x : container) {
		outStream << std::left << std::setw(7) << std::setprecision(5) << x.first.getRelativeGrowth() << std::setw(5) << "%:" << std::setw(30) << x.first.getStadtnamen() << std::setw(30) << x.first.getBundesland() << x.first.getBevoelkerung2011() << endl;
	}
	outFile << outStream.str();
	outFile.close();
}

void outputToFile(std::vector<Town> container) {
	std::stringstream outStream;
	std::ofstream outFile("Staedte.txt", std::ios::out);
	for (auto x : container) {
		outStream << std::left << std::setfill('.') << std::setw(30) << x.getStadtnamen() << std::setw(30) << x.getBundesland() << x.getBevoelkerung2011() << endl;
	}
	outFile << outStream.str();
	outFile.close();
}

int main() {
	setlocale(LC_ALL, "");
	std::string bundesland, name, tmp;
	int gesamtbevoelkerung1984, mBevoelkerung1984, wBevoelkerung1984, gesamtbevoelkerung2011, mBevoelkerung2011, wBevoelkerung2011;
	int userInput, namesUsedOnce{ 0 };

	std::ifstream inFile("zensus.txt", std::ios::in);
	if (!inFile) {
		std::cerr << "Fehler beim Öffnen" << endl;
		exit(EXIT_FAILURE);
	}

	std::vector<Town> staedte;
	std::vector<Town> staedteTMP;
	std::vector<std::pair<Town, double>>relativeGrowth;
	std::map<std::string, int>multipleTownNames;
	std::map<std::string, int>bundeslandEinweohner;
	std::vector<std::pair<std::string, int>>multipleTownNamesSorted;

	while (!inFile.eof()) {
		std::getline(inFile, bundesland, '\n');
		std::getline(inFile, name, '\n');

		inFile >> gesamtbevoelkerung2011 >> mBevoelkerung2011 >> wBevoelkerung2011 >> gesamtbevoelkerung1984 >> mBevoelkerung1984 >> wBevoelkerung1984;
		std::getline(inFile, tmp);

		if (bundesland != "") {
			staedte.emplace_back(bundesland, name, gesamtbevoelkerung2011, mBevoelkerung2011, wBevoelkerung2011, gesamtbevoelkerung1984, mBevoelkerung1984, wBevoelkerung1984);
		}
	}

	do {
		cout << "[1] Alle Städte sortiert nach Namen in Datei speichern" << endl;
		cout << "[2] Einwohnerzahlen der Bundesländer ausgeben" << endl;
		cout << "[3] Städte sortiert nach größtem reletivem Wachstum in Datei Speichern" << endl;
		cout << "[4] Mehrfach vorkommende Städtenamen ausgeben" << endl << endl;
		cout << "[9] Programm beenden" << endl;
		cout << "Ihre Wahl: ";
		cin >> userInput;

		switch (userInput) {
		case 1:
			staedteTMP = staedte;
			std::sort(staedteTMP.begin(), staedteTMP.end());

			//outputToFile(staedteTMP);
			break;


		case 2:
			for (const auto& x : staedte) {
				bundeslandEinweohner.emplace(x.getBundesland(), bundeslandEinweohner[x.getBundesland()] += x.getBevoelkerung2011());
			}

			for (auto itr = bundeslandEinweohner.begin(); itr != bundeslandEinweohner.end(); itr++) {
				cout << std::left << std::setfill('.') << std::setw(30) << itr->first << itr->second << endl;
			}
			std::setfill(' ');
			break;


		case 3:
			for (const auto& x : staedte) {
				relativeGrowth.push_back(std::make_pair(x, x.getRelativeGrowth()));
			}

			std::sort(relativeGrowth.rbegin(), relativeGrowth.rend(),
				[](const auto& a, const auto& b) {return a.second < b.second; }
			);
			outputToFile(relativeGrowth);
			break;


		case 4:
			for (const auto& x : staedte) {
				multipleTownNames.emplace(x.getStadtnamen(), multipleTownNames[x.getStadtnamen()]++);
			}
			for (auto itr = multipleTownNames.begin(); itr != multipleTownNames.end(); itr++) {
				multipleTownNamesSorted.push_back(std::make_pair(itr->first, itr->second));
			}

			std::sort(multipleTownNamesSorted.rbegin(), multipleTownNamesSorted.rend(),
				[](const auto& a, const auto& b)
				{
					if (a.second == b.second) {
						return a.first > b.first;
					}
					else {
						return a.second < b.second;
					}
				});
			for (const auto& x : multipleTownNamesSorted) {
				if (x.second > 1) {
					cout << std::left << std::setfill('.') << std::setw(20) << x.first << x.second << endl;
				}
				else {
					++namesUsedOnce;
				}
			}
			cout << endl << "Eindeutige Namen: " << namesUsedOnce;
			break;


		case 9: break;

		default:
			cout << "ungültige Eingabe" << endl;
			break;
		}

	} while (userInput != 9);

}