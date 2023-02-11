#pragma once

#include<fstream>

#include "loadingImages.h"


class loadingFieldResourses : public loadingImages
{
private:
	std::string saveFolder = "save/";
public:
	loadingFieldResourses() {

	}
	~loadingFieldResourses()
	{
#ifdef DEBUG
		std::cout << "loadingFieldResourses::deconstructor\n";
#endif // DEBUG
	}

	///example path: lvl1.txt
	void openMap(std::string path, std::vector<std::vector<cell>>& V) {
		std::cout << "file::file\n";
		std::ifstream file((this->saveFolder + path).c_str());
		if (file.is_open())
		{
			std::cout << "file::open\n";
			std::string tempStr = "";

			int l = 0, m = 0, k = 0;
			while (std::getline(file, tempStr))
			{
				k = 0;
				m = 0;
				while (tempStr[k] != '\0')
				{
					if (tempStr[k] == '/')
					{
						k++;
					}
					if (tempStr[k] == '\0')
					{
						break;
					}

					V[l][m].obj = static_cast<uint8_t>(tempStr[k] - '0');
					V[l][m].objHp = static_cast<uint8_t>(tempStr[++k] - '0');
					m++;
					k++;
				}
				l++;

			}
			tempStr.clear();
			file.close();
		}
#ifdef DEBUG
		else
		{
			std::cout << "loadingFieldResourses::openMap::loadingError file was't open\n";
		}
#endif // DEBUG

}

};

