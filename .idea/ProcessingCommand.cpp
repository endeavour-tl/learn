#include "ProcessingCommand.h"

std::string ProcessingCommand::getInputCommand() {
	std::string retString;
	std::string tempString;
	//std::cout << "00" << std::endl;
	while (true) {
		/*std::cout << "0" << std::endl;*/
		std::getline(std::cin, tempString);
		/*std::cout << "1" << std::endl;*/
		if (tempString.empty()) {
			continue;
		}
		if (tempString[tempString.size() - 1] == '\\') {
			/*std::cout << "2" << std::endl;*/
			tempString = tempString.substr(0, tempString.size() - 1);
			retString += tempString;
		}
		else {
			retString += tempString;
			break;
		}
	}
	//std::cout << "4" << std::endl;
	return retString;
}


std::map<std::string, int> ProcessingCommand::_init_() {
	std::map<std::string, int> firstCommand;
	firstCommand[std::string("cd")] = 0;
	firstCommand[std::string("ls")] = 1;
	firstCommand[std::string("mkdir")] = 2;
	firstCommand[std::string("echo")] = 3;
	firstCommand[std::string("cat")] = 4;
	firstCommand[std::string("cp")] = 5;
	firstCommand[std::string("touch")] = 6;
	firstCommand[std::string("rm")] = 7;
	firstCommand[std::string("rmdir")] = 8;
	firstCommand[std::string("who")] = 9;
	firstCommand[std::string("rname")] = 10;
	firstCommand[std::string("exit")] = 11;
	return firstCommand;
}

std::string ProcessingCommand::separationCommand(std::string command) {
	std::string retCommand;
	std::istringstream input(command);
	input >> retCommand;
	return retCommand;
}

std::vector<std::string> ProcessingCommand::divisionCommand(std::string command) {
	std::vector<std::string> retCommand;
	int doubleQuotationMarks = 0;	//0,1,2
	int doubleQuotationMarksFirst = -1, doubleQuotationMarksSecond = -1;
	int wordCount = 0;
	for (int i = 0; i < command.size(); i++) {
		if (command[i] == '\"') {
			doubleQuotationMarks++;
			if (doubleQuotationMarks == 1) {
				doubleQuotationMarksFirst = i + 1;
			}
			else {
				doubleQuotationMarksSecond = i - 1;
				doubleQuotationMarks = 0;
				retCommand.push_back(command.substr(doubleQuotationMarksFirst,
					doubleQuotationMarksSecond - doubleQuotationMarksFirst + 1));
			}
		}
		else if (command[i] == ' ') {
			if (doubleQuotationMarks == 0) {
				if (wordCount != 0) {
					int first = i - wordCount;
					if (first < 0) {
						std::cout << first << " " << i << " " << wordCount << std::endl;
						exit(0);
					}
					retCommand.push_back(command.substr(i - wordCount, wordCount));
					wordCount = 0;
				}
			}
			else {
				continue;
			}
		}
		else if (doubleQuotationMarks == 0) {
			wordCount++;
		}
	}
	if (wordCount != 0) {
		retCommand.push_back(command.substr(command.size() - wordCount, wordCount));
	}
	return retCommand;
}

void ProcessingCommand::manageCommand(std::string command, Command tempCommand) {
	std::map<std::string, int> firstCommand = _init_();
	//std::cout << "11" << std::endl;
	std::string userFirstCommand = separationCommand(command);
	//std::cout << "22" << std::endl;
	auto it = firstCommand.find(userFirstCommand);
	//std::cout << "33" << std::endl;
	if (it == firstCommand.end()) {
		std::cout << "Input error,please re-type!" << std::endl;
	}
	else {
		switch (it->second)
		{
		case 0:
			tempCommand.cd(); break;
		case 1:
			tempCommand.ls(); break;
		case 2:
			tempCommand.mkdir(); break;
		case 3:
			tempCommand.echo(); break;
		case 4:
			tempCommand.cat(); break;
		case 5:
			tempCommand.cp(); break;
		case 6:
			tempCommand.touch(); break;
		case 7:
			tempCommand.rm(); break;
		case 8:
			tempCommand.rmdir(); break;
		case 9:
			tempCommand.who(); break;
		case 10:
			tempCommand.rname(); break;
		case 11:
			tempCommand.exit(); break;
			/*default:
				std::cout << "输入错误请重新输入" << std::endl;
				break;*/
		}
	}

}

void ProcessingCommand::run() {
	std::string current_dir = "/home/a789we=-+4/456sfds";
	while (true) {
		std::cout << current_dir;
		std::string str = getInputCommand();  //获得输入命令
		//std::cout << str << std::endl;
		std::vector<std::string> vet = divisionCommand(str);  //将输入命令进行分割
		Command command(vet);				//将command进行初始化，并传入分割后的命令
		Catalogue catalogue(current_dir);   //将catalogue进行初始化，并传入当前目录
		std::vector<std::pair<std::string, int>> pathOrCatalogue = command.getFileOrCatalogue();   //调用command的函数，返回输入形式的文件名或者目录名
		if (pathOrCatalogue.size() == 1 && pathOrCatalogue[0].first == "error" && pathOrCatalogue[0].second == 0) {			   //判断文件名和目录名之间是否有其他无效参数，有就重新输入
			continue;
		}
		/*std::cout << "1" << std::endl;*/
		std::vector<std::pair<std::string, int>> inputAbsoluteAddress;					//存储文件或者目录的绝对路劲，int 1表示文件，2表示路径			
		for (int i = 0; i < pathOrCatalogue.size(); i++) {
			//std::cout << pathOrCatalogue[i].first << "  " << pathOrCatalogue[i].second << std::endl;
			//std::cout << catalogue.getFileAddress(pathOrCatalogue[i].first) << std::endl;			//调用catalogue的getFileAddress函数，返回文件或者目录的绝对地址
			/*std::cout << "1" << std::endl;*/
			inputAbsoluteAddress.push_back(std::pair<std::string, int>(catalogue.getFileAddress(pathOrCatalogue[i].first), pathOrCatalogue[i].second)); //插入文件或者目录的绝对路劲，int 1表示文件，2表示路径
			/*std::cout << "2" << std::endl;
			std::cout << catalogue.getFileAddress(pathOrCatalogue[i].first) << std::endl;*/
		}
		command.copyAbsoluteAddress(inputAbsoluteAddress);     //将得到的文件或者目录的绝对路径进行拷贝，使command类的函数能访问到输入的绝对路径
		/*std::cout << "4" << std::endl;*/
		manageCommand(str, command);           //执行输入的第一个参数命令
	}
}