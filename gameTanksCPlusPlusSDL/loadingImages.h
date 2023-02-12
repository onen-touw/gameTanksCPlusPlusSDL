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
			errors::errorStatus = ErrorsCodes::IMG_LOADING_ERROR;
			return;
		}

		/// optimization imgSurface for target surface
		/*flower = SDL_ConvertSurface(flower, gameSettings::winSetting.surface->format, NULL);
		}*/
		if (flower == nullptr) {
			errors::errorStatus = ErrorsCodes::IMG_LOADING_ERROR;
			success = false;
		}
		if (!success)
		{
			#ifdef DEBUG
				std::cout << "loadingResourses::LoadingImageError:: id# "<< enumName << "\n";
				system("pause");
			#endif // DEBUG
			return;
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
			//std::cout << vPaths[i].path << "<< loading #" << i << "\n";
			this->load(vPaths[i].path, vPaths[i].id);
		}
	}

	SDL_Surface* loadOneImg(std::string path) {
		SDL_Surface* flower = IMG_Load(path.c_str());
		if (flower == nullptr) {
			errors::errorStatus = ErrorsCodes::IMG_LOADING_ERROR;
#ifdef DEBUG
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			system("pause");
#endif // DEBUG
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

