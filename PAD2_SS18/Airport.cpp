#include"Airport.h"

Airport::Airport() {}

Airport::Airport(const std::string& iniata, const std::string& inairportname, const std::string& incity, const std::string& inabbreviation, const std::string& incountry, const double& inlat, const double& inlon)
	:iata(iniata), airportname(inairportname), city(incity), abbreviation(inabbreviation), country(incountry), lat(inlat), lon(inlon)
{}




std::string Airport::getIATA()const {
	return iata;
}

std::string Airport::getAirportName()const {
	return airportname;
}

std::string Airport::getCity()const {
	return city;
}

std::string Airport::getStateAbbr()const {
	return abbreviation;
}

std::string Airport::getCountry()const {
	return country;
}

double Airport::getLat()const {
	return lat;
}

double Airport::getLon()const {
	return lon;
}