#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "headers/Level1Map.h"	//level 1
#include "headers/Level2Map.h"	//level 2

int main()			//our main
{  
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(400, 250), "Start Menu");	//new window

	sf::Image *icon = new sf::Image;			//icon of blue mushroom
	icon->loadFromFile("images/Blue.png");			//
	window->setIcon(100,100,icon->getPixelsPtr());		//

	LevelMap *level;		//our buffer pointer at any level

	int numberOfLevel = 1;		//starting level

    while (window->isOpen())		//main cycle
    { 
		switch (numberOfLevel) {
				case 1:	 level = new Level1Map(*window, true); break;				//loading "pure" level 1
				case 11: level = new Level1Map(*window, false); level->loadFromFile(1); break;	//loading level 1 from save file 1
				case 12: level = new Level1Map(*window, false); level->loadFromFile(2); break;	//								 2
				case 13: level = new Level1Map(*window, false); level->loadFromFile(3); break;	//								 3
				case 2:	 level = new Level2Map(*window); break;					//loading "pure" level 2
				case 21: level = new Level2Map(*window); level->loadFromFile(1); break;		//loading level 2 from save file 1
				case 22: level = new Level2Map(*window); level->loadFromFile(2); break;		//								 2
				case 23: level = new Level2Map(*window); level->loadFromFile(3); break;		//								 3
				default: window->close(); break;												//unexpected case
			};
		numberOfLevel = level->update();	//game works here
		delete level;				//freeing memory
	}

	delete icon;		//freeing memory
	delete window;		//
    return 0;			//success
}
