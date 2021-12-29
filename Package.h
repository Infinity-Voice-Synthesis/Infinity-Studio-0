#pragma once

#include <string>
#include <list>

class Package
{
	static Package _package;

	Package();
	~Package();

public:
	static Package& getPackage();

	class Param {
	public:
		std::string name;
		double vMax;
		double vMin;
		double vDefault;
	};

	//Éù¿â
	std::list<std::string> getLibraryAvailable();
	std::string getEngineName(std::string library);
	std::list<std::string> getLibraryTimbre(std::string library);
	std::string getLibraryTimbreDefault(std::string library);

	//ÒýÇæ
	std::list<std::string> getEngineAvailable();
	std::list<Package::Param> getEngineParam(std::string engine);//ugly!
};

