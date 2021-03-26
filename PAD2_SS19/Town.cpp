#include"Town.h"

Town::Town(const std::string& inBundesland, const std::string& inName, const int& inGesamtbevoelkerung2011, const int& inmBevoelkerung2011, const int& inwBevoelkerung2011,
	const int& inGesamtbevoelkerung1984, const int& inmBevoelkerung1984, const int& inwBevoelkerung1984)
	:bundesland(inBundesland), name(inName),
	gesamtbevoelkerung2011(inGesamtbevoelkerung2011), mBevoelkerung2011(inmBevoelkerung2011), wBevoelkerung2011(inwBevoelkerung2011),
	gesamtbevoelkerung1984(inGesamtbevoelkerung1984), mBevoelkerung1984(inmBevoelkerung1984), wBevoelkerung1984(inwBevoelkerung1984)
{}

std::string Town::getStadtnamen() const {
	return name;
}

std::string Town::getBundesland() const {
	return bundesland;
}

int Town::getBevoelkerung2011() const {
	return gesamtbevoelkerung2011;
}

double Town::getRelativeGrowth()const {
	return (static_cast<double>(gesamtbevoelkerung2011) / gesamtbevoelkerung1984) * 100;
}
