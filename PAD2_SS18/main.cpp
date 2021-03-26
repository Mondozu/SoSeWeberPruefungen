#include<map>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include"Airport.h"

using std::cout;
using std::cin;
using std::endl;

//möglich mit tolower
std::string uppercase(std::string& inString) {
	for (size_t i = 0; i < inString.length(); i++){
		inString[i] = std::toupper(inString[i]);
	}
	return inString;
}


int main() {
	std::string dummy, iata, name, city, abbreviation, country, state, userin;
	char comma;
	double lat, lon;
	int menuSelection;

	std::map<std::string, std::string>stateAbbMap;////
	std::ifstream inAbb("stateabb.txt", std::ios::in);
	std::getline(inAbb, dummy);
	while (std::getline(inAbb, state, '\t').good()) {
		std::getline(inAbb, abbreviation);
		stateAbbMap.emplace(abbreviation, state);
	}
	inAbb.close();

	std::map<std::string, Airport>airports;////
	std::ifstream inAirports("airports.txt", std::ios::in);
	std::getline(inAirports, dummy);
	while ((inAirports >> std::quoted(iata)).good()) {
		inAirports >> comma >> std::quoted(name) >> comma >> std::quoted(city) >> comma 
			>> std::quoted(abbreviation) >> comma >> std::quoted(country) >> comma >> lat >> comma >> lon;
		Airport tmpAirport{ iata, name, city, abbreviation, country, lat, lon };
		airports.emplace(iata, tmpAirport);
	}
	inAirports.close();

	do {
		std::string a = "tesASDt string!";
		cout<<uppercase(a);
		cout
			<< "[1] Infos zu IAIA-Code oder Stadt auf Konsole ausgeben" << endl
			<< "[2] Anzahl Flughaefen in einzelnden Staaten/Territorien auf Konsole Ausgeben" << endl
			<< "[3] Noerdlichsten bzw. suedlichsten Flughafen auf Konsole ausgeben" << endl
			<< "[4] Entfernung zwischen zwei Flughäfen bestimmen" << endl << endl
			<< "[9] Beenden" << endl
			<< "Ihre Wahl: ";
		cin >> menuSelection;

		switch (menuSelection) {
		case 1: {
			cout << "Eingabe: ";
			cin >> userin;
			bool foundsth{ false };
			std::map<std::string, Airport>::iterator aMapItr = airports.find(userin);
			std::map<std::string, std::string>::iterator abbItr;

			if (aMapItr == airports.end()) { //Wenn kein IATA Code dem userin entspricht
				for (aMapItr = airports.begin(); aMapItr != airports.end(); aMapItr++) { //Durchsuche die map nach übereinstimmenden Städtenamen
					if (aMapItr->second.getCity() == userin) {
						abbItr = stateAbbMap.find(aMapItr->second.getStateAbbr());
						cout << aMapItr->second.getAirportName() << ", " << aMapItr->second.getCity() << ", " << abbItr->second 
							<< "(" << aMapItr->second.getStateAbbr() << "), " << aMapItr->second.getCountry()
							<< '\t' << aMapItr->second.getLat() << '\t' << aMapItr->second.getLon() << endl;
						foundsth = true;
					}
				}
			}
			else { //Wenn es einen IATA Code gibt
				abbItr = stateAbbMap.find(aMapItr->second.getStateAbbr());
				cout << aMapItr->second.getAirportName() << ", " << aMapItr->second.getCity() << ", " << abbItr->second 
					<< "(" << aMapItr->second.getStateAbbr() << "), " << aMapItr->second.getCountry()
					<< '\t' << '\t' << aMapItr->second.getLat() << '\t' << aMapItr->second.getLon() << endl;
				foundsth = true;
			}
			if (!foundsth) {
				cout << "Keine Uebereinstimmungen" << endl;
			}
		}break;

		case 2: {
			std::map<std::string, int>airportsInState;
			for (auto i = airports.begin(); i != airports.end(); i++) {
				std::string state = stateAbbMap.find(i->second.getStateAbbr())->second;//Get statename from Abbreviation
				airportsInState.emplace(state, airportsInState[state]++);
			}

			std::multimap<int, std::string>sorted;
			for (auto i = airportsInState.begin(); i != airportsInState.end(); i++) {
				sorted.emplace(i->second, i->first);
			}
			cout << std::left << std::setw(35) << "Staat/Territorium" << "Anz. Flughaefen" << endl;
			for (auto i = sorted.begin(); i != sorted.end(); i++) {
				cout << std::left << std::setw(35) << i->second << i->first << endl;
			}

		}break;

		case 3: {
			std::map<std::string, Airport>::iterator minItr = airports.begin();
			std::map<std::string, Airport>::iterator maxItr = airports.begin();

			for (auto i = airports.begin(); i != airports.end(); i++) {
				if (i->second.getLat() < minItr->second.getLat()) {
					minItr = i;
				}

				if (i->second.getLat() > maxItr->second.getLat()) {
					maxItr = i;
				}
			}
			cout << "Alle Flughaefen:" << endl;

			cout << "Noerdlichster: " << maxItr->second.getAirportName() << " in " << maxItr->second.getCity() << endl;
			cout << "Suedlichster: " << minItr->second.getAirportName() << " in " << minItr->second.getCity() << endl << endl;


			minItr = airports.begin();
			maxItr = airports.begin();

			for (auto i = airports.begin(); i != airports.end(); i++) {
				if (i->second.getLon() <= -68 && i->second.getLon() >= -125) {
					if ((i->second.getLat() < minItr->second.getLat())) {
						minItr = i;
					}
					if (i->second.getLat() > maxItr->second.getLat()) {
						maxItr = i;
					}
				}
			}

			cout << "Flughaefen im Kerngebiet:" << endl;
			cout << "Noerdlichster: " << maxItr->second.getAirportName() << " in " << maxItr->second.getCity() << endl;
			cout << "Suedlichster: " << minItr->second.getAirportName() << " in " << minItr->second.getCity() << endl << endl;
		}break;

		case 4: {
			//Lat -> Breite, Lon -> Länge
			auto itr1 = airports.begin();
			auto itr2 = airports.begin();

			do {
				std::string inIATA;
				cout << "Ersten IATA Code eingeben: ";
				cin >> inIATA;

				//make toupper mit algorithm
				//std::transform(inIATA.begin(), inIATA.end(), inIATA.begin(), std::toupper);

				itr1 = airports.find(inIATA);
				if (itr1 == airports.end()) {
					cout << "Fehlerhafte Eingabe" << endl;
				}
			} while (itr1 == airports.end());

			do {
				std::string inIATA;
				cout << "Zweiten IATA Code eingeben: ";
				cin >> inIATA;

				itr2 = airports.find(inIATA);
				if (itr2 == airports.end()) {
					cout << "Fehlerhafte Eingabe" << endl;
				}
			} while (itr2 == airports.end());

			double kath1{ std::abs(itr1->second.getLat() - itr2->second.getLat()) * 111.3 };
			double kath2{ std::abs(itr1->second.getLon() - itr2->second.getLon()) * 
				(std::cos(std::abs((itr1->second.getLat() + itr2->second.getLat()) / 2) * (std::acos(-1.0) / 180)))*111.3 };
			double distance{ std::sqrt(kath1 * kath1 + kath2 * kath2) };

			cout << "Entfernung: "<< distance << "km" << endl;

		}break;
		case 9: break;
		default:
			cout << "Eingabe fehlerhaft" << endl;
			break;
		}
	} while (menuSelection != 9);

}