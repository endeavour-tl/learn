#include"Command.h"

Command::Command(std::vector<std::string> divisionCommandVector):divisionCommandVector(divisionCommandVector) {
	commandOperator.insert(std::pair<std::string, int>("-l", 1));
	commandOperator.insert(std::pair<std::string, int>("--list", 1));
	commandOperator.insert(std::pair<std::string, int>("-a", 2));
	commandOperator.insert(std::pair<std::string, int>("--all", 2));
	commandOperator.insert(std::pair<std::string, int>("-p", 3));
	commandOperator.insert(std::pair<std::string, int>("--parent", 3));
	commandOperator.insert(std::pair<std::string, int>("-r", 4));
	commandOperator.insert(std::pair<std::string, int>("--recurse", 4));
	commandOperator.insert(std::pair<std::string, int>("-f", 5));
	commandOperator.insert(std::pair<std::string, int>("-force", 5));
	Obtain_instruction();
}

void Command::Obtain_instruction() {
	for (int i = 1; i < divisionCommandVector.size(); i++) {
		if (divisionCommandVector[i][0] == '-') {
			Obtain_instructionDivisionCommandVector.push_back(divisionCommandVector[i]);
		}
	}
}

void Command::cd() {
	if (copyInputAbsoluteAddress.size() == 1 && copyInputAbsoluteAddress[0].second == 2) {
		std::cout << copyInputAbsoluteAddress[0].first << "  " << copyInputAbsoluteAddress[0].second << std::endl;
		//TODO:void command::cd(string dir);
		std::cout << "void command::cd(string dir);" << std::endl;
	}
	else {
		std::cout << "Directory entry error!" << std::endl;
		return;
	}
}

void Command::ls() {
	bool list_option = false, all_option = false;
	std::vector<int> commandNumber;
	for (int i = 0; i < Obtain_instructionDivisionCommandVector.size(); i++) {
		auto it = commandOperator.find(Obtain_instructionDivisionCommandVector[i]);
		if (it == commandOperator.end()) {
			std::cout << "ls directive: argument call error!" << std::endl;
			return;
		}
		else {
			switch (it->second)
			{
			case 1:
				commandNumber.push_back(it->second); break;
			case 2:
				commandNumber.push_back(it->second); break;
			default:
				std::cout << "ls directive: argument call error!" << std::endl;
				return;
			}
		}
	}
	if (Obtain_instructionDivisionCommandVector.empty()) {
		std::cout << "ls no - operation, the default parameter is invoked!" << std::endl;
		return;
	}
	if (commandNumber.size() == 2) {
		list_option = true;
		all_option = true;
		std::cout << "The operation of ls - is called with the argument -l -a!" << std::endl;
	}
	else if (commandNumber[0] == 1) {
		std::cout << "ls -l/--list to list file details or directly ll" << std::endl;
		list_option = true;
	}
	else if (commandNumber[0] == 2) {
		std::cout << "The ls -a/--all operation lists all files and directories in the current directory, including hidden a(all)!" << std::endl;
		all_option = true;
	}
	else {
		std::cout << "The parameter of ls - is incorrect!" << std::endl;
	}
	if (copyInputAbsoluteAddress.size() == 1 && copyInputAbsoluteAddress[0].second == 2) {
		std::cout << copyInputAbsoluteAddress[0].first << " " << copyInputAbsoluteAddress[0].second << std::endl;
		//TODO:void command::ls(string dir, bool l, bool a);
		std::cout << "void command::ls(string dir, bool l, bool a);" << std::endl;
	}
	else {
		std::cout<<"Directory entry error" << std::endl;
		return;
	}
}

void Command::mkdir() {
	bool parent_option = false;
	std::vector<int> commandNumber;
	for (int i = 0; i < Obtain_instructionDivisionCommandVector.size(); i++) {
		auto it = commandOperator.find(Obtain_instructionDivisionCommandVector[i]);
		if (it == commandOperator.end()) {
			std::cout << "mkdir directive: argument call error!" << std::endl;
			return;
		}
		else {
			switch (it->second)
			{
			case 3:
				commandNumber.push_back(it->second); break;
			default:
				std::cout << "mkdir directive: argument call error!" << std::endl;
				return;
			}
		}
	}

	if (Obtain_instructionDivisionCommandVector.empty()) {
		std::cout << "mkdir no - operation, call the default parameter!" << std::endl;
		return;
	}
	if (commandNumber.size() >= 2) {
		std::cout << "mkdir - operation, parameter call error!" << std::endl;
	}
	else if (commandNumber[0] == 3) {
		parent_option = true;
		std::cout << "mkdir -p/--parent creates a directory. If there is no parent directory, create p(parent)!" << std::endl;
	}
	else {
		std::cout << "The mkdir - parameter is incorrectly used!" << std::endl;
	}
}

void Command::echo() {
	std::cout << "echo" << std::endl;
}

void Command::cat() {
	if (Obtain_instructionDivisionCommandVector.size() != 0) {
		std::cout << "cat has no '-' instruction" << std::endl;
		return;
	}
	if (copyInputAbsoluteAddress.size() == 2 || copyInputAbsoluteAddress[0].second == 1) {
		std::cout << copyInputAbsoluteAddress[0].first << " " << copyInputAbsoluteAddress[0].second << std::endl;
		//TODO:void cat (string file);
		std::cout << "void cat (string file);" << std::endl;
	}
	else {
		std::cout << "The file address is incorrect!" << std::endl;
		return;
	}
}
void Command::cp() {
	std::vector<std::string> files;
	std::string dir;
	if (Obtain_instructionDivisionCommandVector.size() != 0) {
		std::cout << "cp has no '-' instruction!" << std::endl;
		return;
	}
	for (int i = 0; i < copyInputAbsoluteAddress.size(); i++) {
		if (i == copyInputAbsoluteAddress.size() - 1) {
			if (copyInputAbsoluteAddress[i].second == 2) {
				dir = copyInputAbsoluteAddress[i].first;
				break;
			}
			else {
				std::cout << "The entered directory format is incorrect!" << std::endl;
				return;
			}
		}
		if (copyInputAbsoluteAddress[i].second == 1) {
			files.push_back(copyInputAbsoluteAddress[i].first);
		}
		else {
			std::cout << "The file name is entered in the wrong form. There cannot be a directory in the middle!" << std::endl;
			return;
		}
	}
	if (files.size() == 0) {
		std::cout << "cp The file name is not entered. Please re-enter it!" << std::endl;
		return;
	}
	else {
		//TODO:void cp(vector<string> files, string dir);
		std::cout << "void cp(vector<string> files, string dir);" << std::endl;
	}
}

void Command::touch() {
	std::vector<std::string> files;
	if (Obtain_instructionDivisionCommandVector.size() != 0) {
		std::cout << "touch has no '-' command!" << std::endl;
		return;
	}
	for (int i = 0; i < copyInputAbsoluteAddress.size(); i++) {
		if (copyInputAbsoluteAddress[i].second == 1) {
			files.push_back(copyInputAbsoluteAddress[i].first);
		}
		else {
			std::cout << "File name error!" << std::endl;
			return;
		}
	}
	if (files.size() != 0) {
		//TODO:void touch(vector<string> files);
		std::cout << "void touch(vector<string> files);" << std::endl;
	}
	else {
		std::cout << "The file name cannot be empty!" << std::endl;
		return;
	}
}

void Command::rm() {
	bool recurse_option = false, force_option = false, file_or_dir;//file_or_dir:  0:file ; 1:dir  
	std::vector<int> commandNumber;
	for (int i = 0; i < Obtain_instructionDivisionCommandVector.size(); i++) {
		auto it = commandOperator.find(Obtain_instructionDivisionCommandVector[i]);
		if (it == commandOperator.end()) {
			std::cout << "rm instruction: parameter call error!" << std::endl;
			return;
		}
		else {
			switch (it->second)
			{
			case 4:
				commandNumber.push_back(it->second); break;
			case 5:
				commandNumber.push_back(it->second); break;
			default:
				std::cout << "rm instruction: parameter call error!" << std::endl;
				return;
			}
		}
	}
	if (Obtain_instructionDivisionCommandVector.empty()) {
		std::cout << "rm If no - is displayed, the default parameter is invoked!" << std::endl;
		return;
	}
	if (commandNumber.size() >= 2) {
		std::cout << "Operation of rm -, parameter invocation error!" << std::endl;
		return;
	}
	else if (commandNumber[0] == 4) {
		recurse_option = true;
		std::cout << "rm -r/--recurse operation to delete subdirectories and files" << std::endl;
	}
	else if (commandNumber[0] == 5) {
		force_option = true;
		std::cout << "The ls -f/--force operation is used to forcibly delete the command" << std::endl;
	}
	else {
		std::cout << "The parameter of ls - is incorrect" << std::endl;
		return;
	}
	if (copyInputAbsoluteAddress.size() == 1) {
		if (copyInputAbsoluteAddress[0].second == 1) {
			file_or_dir = false; //���ļ�
		}
		else {
			file_or_dir = true; //��Ŀ¼
		}
	}
	else {
		std::cout << "The file name or directory name is too large!" << std::endl;
		return;
	}
	//TODO:void rm(string file, bool r, bool f, bool file_or_dir);
	std::cout << "void rm(string file, bool r, bool f, bool file_or_dir);" << std::endl;
}

void Command::rmdir() {
	std::vector<std::string> dirs;
	if (Obtain_instructionDivisionCommandVector.size() != 0) {
		std::cout << "rmdir no '-' instruction!" << std::endl;
		return;
	}
	for (int i = 0; i < copyInputAbsoluteAddress.size(); i++) {
		if (copyInputAbsoluteAddress[i].second == 2) {
			dirs.push_back(copyInputAbsoluteAddress[i].first);
		}
		else {
			std::cout << "The entered directory name is incorrect" << std::endl;
			return;
		}
	}
	if (dirs.size() == 0) {
		std::cout << "The directory cannot be empty!" << std::endl;
		return;
	}
	//TODO:void rmdir(vector<string> dirs);
	std::cout << "void rmdir(vector<string> dirs);" << std::endl;
}

void Command::who() {
	std::cout << "who" << std::endl;
}

void Command::rname() {
	std::string target_file, new_filename;
	if (Obtain_instructionDivisionCommandVector.size() != 0) {
		std::cout << "rname No '-' instruction!" << std::endl;
		return;
	}
	if (copyInputAbsoluteAddress.size() != 2) {
		std::cout << "The number of file names is incorrect!" << std::endl;
		return;
	}
	else {
		if (copyInputAbsoluteAddress[0].second != 1 
			|| copyInputAbsoluteAddress[1].second != 1) {
			std::cout << "The directory name cannot be substituted with the file name!" << std::endl;
		}
		int found1 = copyInputAbsoluteAddress[0].first.find_last_of('/');
		int found2 = copyInputAbsoluteAddress[1].first.find_last_of('/');
		if (found1 == copyInputAbsoluteAddress[0].first.npos
			&& found2 == copyInputAbsoluteAddress[1].first.npos) {
			target_file = copyInputAbsoluteAddress[0].first;
			new_filename = copyInputAbsoluteAddress[1].first;
			//TODO:void rname (string target_file, string new_filename);
			std::cout << "void rname (string target_file, string new_filename);" << std::endl;
		}
		else if (found1 != copyInputAbsoluteAddress[0].first.npos
			&& found2 != copyInputAbsoluteAddress[1].first.npos) {
			std::string temp1 = copyInputAbsoluteAddress[0].first.substr(0, found1);
			std::string temp2 = copyInputAbsoluteAddress[1].first.substr(0, found2);
			if (temp1 == temp2) {
				target_file = copyInputAbsoluteAddress[0].first;
				new_filename = copyInputAbsoluteAddress[1].first;
				//TODO:void rname (string target_file, string new_filename);
				std::cout << "void rname (string target_file, string new_filename);" << std::endl;
			}
			else {
				std::cout << "The address of the replacement file name must be correct!" << std::endl;
				return;
			}
		}
		else {
			std::cout << "The address of the replacement file name must be correct!" << std::endl;
			return;
		}
	}
}

void Command::exit() {
	std::cout << "exit" << std::endl;
}

int Command::judge_path(std::string path) {
	std::string file_path = "(\\.{0,2}/([\\w\\s\\.\\-\\:\'\"()+*=;,]+/)*)?[\\w\\.\\-\\:\'\"()+*=;,]+\\.[\\w]+";
	std::string directory_path = "\\.{0,2}(/[\\w\\s\\.\\-\\:\'\"()+*=;,]+)+/?|\\.{1,2}/?";
	regex file_path_regex(file_path);
	regex dir_path_regex(directory_path);
	if (regex_match(path, file_path_regex))return 1; //�����ļ�����׼�򷵻�1
	else if (regex_match(path, dir_path_regex))return 2;  //����Ŀ¼����׼����2
	else return 0;  //���򷵻�0
}

std::vector<std::pair<std::string,int>>Command::getFileOrCatalogue() {
	std::vector<std::pair<std::string,int>> retVecter;
	bool first = false;   //first����ָ���ļ�����Ŀ¼��ʼ
	for (int i = 0; i < divisionCommandVector.size(); i++) {
		if (judge_path(divisionCommandVector[i]) == 1) {
			retVecter.push_back(std::pair<std::string, int>(divisionCommandVector[i], 1));
			first = true;
		}
		else if (judge_path(divisionCommandVector[i]) == 2) {
			retVecter.push_back(std::pair<std::string, int>(divisionCommandVector[i], 2));
			first = true;
		}
		else {
			if (first) {
				std::cout << "Disable invalid values after file/directory names" << std::endl;
				retVecter.clear();
				retVecter.push_back(std::pair<std::string, int>("error", 0)); 
				return retVecter;					//����һ��error�������жϣ�����������
			}
		}
	}
	return retVecter;			//Ψһ������ȷֵ�ĵط�
}

void Command::copyAbsoluteAddress(std::vector <std::pair<std::string,int>> tempVector) {
	/*std::cout << "copy_1" << std::endl;*/
	/*copy(tempVector.begin(), tempVector.end(), copyInputAbsoluteAddress.begin());*/
	for (int i = 0; i < tempVector.size(); i++) {
		copyInputAbsoluteAddress.push_back(tempVector[i]);
	}
	/*std::cout << "copy_2" << std::endl;*/
}