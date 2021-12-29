#include "Package.h"

Package Package::_package;

Package& Package::getPackage()
{
	return Package::_package;
}

Package::Package()
{

}

Package::~Package()
{

}

std::list<std::string> Package::getLibraryAvailable()
{
	return std::list<std::string>();
}

std::string Package::getEngineName(std::string library)
{
	return std::string();
}

std::list<std::string> Package::getLibraryTimbre(std::string library)
{
	return std::list<std::string>();
}

std::string Package::getLibraryTimbreDefault(std::string library)
{
	return std::string();
}

std::list<Package::Param> Package::getEngineParam(std::string engine)
{
	return std::list<Package::Param>();
}

//

std::list<std::string> Package::getEngineAvailable()
{
	return std::list<std::string>();
}
