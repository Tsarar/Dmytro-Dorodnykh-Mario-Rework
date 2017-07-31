#pragma once

#include "LevelMap.h"	//to save our map
#include "Save.h"	//save files

class SaveWindow {
	sf::Texture *saveTexture,* escTexture;		//textures
	sf::Sprite *save1, *save2, *save3, *esc;	//sprites
	int *stand,*menuNum;				//for arrows control
	sf::Clock *cooldownClock;			//for arrows delay
	sf::Vector2u *sizeVector;			//in case of window size change
	sf::RenderWindow &window;			//for errors
	class LevelMap &map;				//to write to the map
	Save *saveFile1, *saveFile2, *saveFile3;	//our save files
public:
	SaveWindow(sf::RenderWindow &_window, LevelMap &map);

	~SaveWindow();

	int run(sf::RenderWindow &window, int mode);

	void initializeSave(int numOfSave,Save *save);

	int hashFromFile(int numOfSave) const;

	};