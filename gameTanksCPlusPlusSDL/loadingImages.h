#pragma once
#include"globals.h"

class loadingImages
{
protected:
	std::vector<SDL_Surface*>images;

private:
	void createImageVector(size_t size) {
		images.resize(size);
	}

	void load(std::string path, unsigned enumName) {
		bool success = true;
		SDL_Surface* flower = IMG_Load(path.c_str());
		if (flower == nullptr) {
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			success = false;
			return;
		}

		/// optimization imgSurface for target surface
		/*flower = SDL_ConvertSurface(flower, gameSettings::winSetting.surface->format, NULL);
		if (flower == nullptr) {
			std::cout << "Can't convert: " << SDL_GetError() << std::endl;
			success = false;
			return;
		}*/
		if (!success)
		{
#ifdef DEBUG
			std::cout << "loadingResourses::LoadingImageError:: id# "<< enumName << "\n";
			system("pause");
#endif // DEBUG

		}
		images[enumName] = flower;
		return;
	}


public:
	loadingImages() {

	}
	~loadingImages()
	{
#ifdef DEBUG
		std::cout << "loadingImages::deconstructor\n";
#endif // DEBUG
		if (this->images.size() > 0)
		{
			for (int i = 0; i < this->images.size(); i++)
			{
				SDL_FreeSurface(this->images[i]);
			}
			this->images.clear();
		}
	}

	SDL_Surface* getImage(unsigned enumName) {
		return images[enumName];
	}

	void loadImages(std::vector<imagePath>vPaths) {

		this->createImageVector(vPaths.size());

		for (int i = 0; i < this->images.size(); i++)
		{
			std::cout << vPaths[i].path << "<< loading #" << i << "\n";
			this->load(vPaths[i].path, vPaths[i].id);
		}
	}

	SDL_Surface* loadOneImg(std::string path) {
		SDL_Surface* flower = IMG_Load(path.c_str());
		if (flower == nullptr) {
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			system("pause");
			exit(-2);
		}
		return flower;
	}

	void logOut() {
		for (int i = 0; i < images.size(); i++)
		{
			if (images[i] != nullptr)
			{
				std::cout << "picture uploaded:: #" << i << "\n";
			}
		}
	}

};

