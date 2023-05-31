#pragma once
#include<iostream>
#include<map>
#include <regex>
#include<vector>
#include<array>
#include<algorithm>
using std::regex;
using std::regex_match;
class Command {

public:
	Command(std::vector<std::string> divisionCommandVector);
	void Obtain_instruction();
	void cd();
	void ls();
	void mkdir();
	void echo();
	void cat();
	void cp();
	void touch();
	void rm();
	void rmdir();
	void who();
	void rname();
	void exit();
	int judge_path(std::string path);
	void copyAbsoluteAddress(std::vector <std::pair<std::string ,int>> tempVector);
	std::vector<std::pair<std::string,int>> getFileOrCatalogue();
private:
	std::map<std::string, int> commandOperator;
	std::vector<std::string> divisionCommandVector;
	std::vector<std::string> Obtain_instructionDivisionCommandVector;
	std::vector<std::pair<std::string,int>> copyInputAbsoluteAddress;
};

