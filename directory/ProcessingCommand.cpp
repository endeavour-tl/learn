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
				std::cout << "�����������������" << std::endl;
				break;*/
		}
	}

}

void ProcessingCommand::run() {
	std::string current_dir = "/home/a789we=-+4/456sfds";
	while (true) {
		std::cout << current_dir;
		std::string str = getInputCommand();  //�����������
		//std::cout << str << std::endl;
		std::vector<std::string> vet = divisionCommand(str);  //������������зָ�
		Command command(vet);				//��command���г�ʼ����������ָ�������
		Catalogue catalogue(current_dir);   //��catalogue���г�ʼ���������뵱ǰĿ¼
		std::vector<std::pair<std::string, int>> pathOrCatalogue = command.getFileOrCatalogue();   //����command�ĺ���������������ʽ���ļ�������Ŀ¼��
		if (pathOrCatalogue.size() == 1 && pathOrCatalogue[0].first == "error" && pathOrCatalogue[0].second == 0) {			   //�ж��ļ�����Ŀ¼��֮���Ƿ���������Ч�������о���������
			continue;
		}
		/*std::cout << "1" << std::endl;*/
		std::vector<std::pair<std::string, int>> inputAbsoluteAddress;					//�洢�ļ�����Ŀ¼�ľ���·����int 1��ʾ�ļ���2��ʾ·��			
		for (int i = 0; i < pathOrCatalogue.size(); i++) {
			//std::cout << pathOrCatalogue[i].first << "  " << pathOrCatalogue[i].second << std::endl;
			//std::cout << catalogue.getFileAddress(pathOrCatalogue[i].first) << std::endl;			//����catalogue��getFileAddress�����������ļ�����Ŀ¼�ľ��Ե�ַ
			/*std::cout << "1" << std::endl;*/
			inputAbsoluteAddress.push_back(std::pair<std::string, int>(catalogue.getFileAddress(pathOrCatalogue[i].first), pathOrCatalogue[i].second)); //�����ļ�����Ŀ¼�ľ���·����int 1��ʾ�ļ���2��ʾ·��
			/*std::cout << "2" << std::endl;
			std::cout << catalogue.getFileAddress(pathOrCatalogue[i].first) << std::endl;*/
		}
		command.copyAbsoluteAddress(inputAbsoluteAddress);     //���õ����ļ�����Ŀ¼�ľ���·�����п�����ʹcommand��ĺ����ܷ��ʵ�����ľ���·��
		/*std::cout << "4" << std::endl;*/
		manageCommand(str, command);           //ִ������ĵ�һ����������
	}
}