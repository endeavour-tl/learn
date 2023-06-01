#include"Catalogue.h"

std::string Catalogue::getFileAddress(std::string TempFileCatalogue) {
	std::string retFileCatalogue;
	int pointCount = 0;
	for (int i = 0; i < TempFileCatalogue.size(); i++) {
		if (TempFileCatalogue[0] != '.' && TempFileCatalogue[0] != '/') {
			retFileCatalogue = currentPath + '/' +TempFileCatalogue;
			return retFileCatalogue;
		}
		switch (TempFileCatalogue[i])
		{
		case '/':
			if (pointCount == 0) {
				retFileCatalogue = TempFileCatalogue;
				return retFileCatalogue;
			}
			else if (pointCount == 1) {
				retFileCatalogue = currentPath + TempFileCatalogue.substr(1,TempFileCatalogue.size()-1);
				return  retFileCatalogue;
			}
			else {                //有两个点的
				int found = currentPath.find_last_of('/');
				if (found == currentPath.npos) {
					retFileCatalogue = currentPath + TempFileCatalogue.substr(2, TempFileCatalogue.size() - 2);
				}
				else {
					retFileCatalogue = currentPath.substr(0, found) + TempFileCatalogue.substr(2, TempFileCatalogue.size() - 2);
				}
			}	 
		case '.':
			pointCount++;
			break;
		}
	}
	return retFileCatalogue;;
}