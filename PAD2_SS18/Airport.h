#pragma once
#include<string>
#include<sstream>
class Airport
{
public:
	Airport();
	Airport(const std::string& iniata, const std::string& inairportname, const std::string& incity, const std::string& inabbreviation, const std::string& incountry, const double& inlat, const double& inlon);
	
	std::string getIATA()const;
	std::string getAirportName()const;
	std::string getCity()const;
	std::string getStateAbbr()const;
	std::string getCountry()const;
	double getLat()const;
	double getLon()const;

private:
	std::string iata;
	std::string airportname;
	std::string city;
	std::string abbreviation;
	std::string country;
	double lat;
	double lon;
};