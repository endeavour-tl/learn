#pragma once
#include<iostream>
#include<string>

class Catalogue
{
public:
	Catalogue(std::string currentPath):currentPath(currentPath){}
	std::string getFileAddress(std::string TempFileCatalogue);

private:
	std::string currentPath;
};