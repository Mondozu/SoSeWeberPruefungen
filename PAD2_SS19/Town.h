#pragma once
#include<string>

class Town {
public:
	Town();
	Town(const std::string& inBundesland, const std::string& inName,const int& inGesamtbevoelkerung2011, const int& inmBevoelkerung2011, const int& inwBevoelkerung2011, 
		const int& inGesamtbevoelkerung1984, const int& inmBevoelkerung1984, const int& inwBevoelkerung1984);

	std::string getStadtnamen() const;
	std::string getBundesland() const;
	int getBevoelkerung2011() const;

	double getRelativeGrowth()const;

private:
	std::string bundesland;
	std::string name;
	int gesamtbevoelkerung1984;
	int mBevoelkerung1984;
	int wBevoelkerung1984;

	int gesamtbevoelkerung2011;
	int mBevoelkerung2011;
	int wBevoelkerung2011;

};