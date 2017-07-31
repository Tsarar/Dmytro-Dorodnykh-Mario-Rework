#pragma once

#include <SFML/Graphics.hpp>

class DeathMenu {
	sf::Texture *yesButton,*noButton,*textTexture;	//textures
	sf::Sprite *yes,*no,*text;			//sprites
	sf::Vector2u *sizeVector;			//in case of window size change
	int *stand,*menuNum;				//for controlling menu with arrows
	sf::Clock *cooldownClock;			//for arrows delay

public:
	DeathMenu();

	~DeathMenu();

	bool run(sf::RenderWindow &window);		//main procedure

	};