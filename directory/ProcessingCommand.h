#pragma once
#include <iostream>
#include<sstream> 
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include "Command.h"
#include "Catalogue.h"

class ProcessingCommand {
public:
    void run();
private:
	std::map<std::string, int> _init_();
	std::string separationCommand(std::string command);
	std::vector<std::string> divisionCommand(std::string command);
	std::string getInputCommand();
	void manageCommand(std::string command, Command tempCommand);
};
