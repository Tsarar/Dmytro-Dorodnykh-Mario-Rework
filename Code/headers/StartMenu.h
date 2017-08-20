#pragma once

#include <SFML/Graphics.hpp>

class StartMenu
	{
		sf::Texture menuTexture1,menuTexture2,menuTexture3,menuTexture4,aboutTexture,controlsTexture;	//textures
		int stand,menuNum;													//for controlling menu with arrows
		sf::Sprite menu1,menu2,menu3,menu4,about,controls;				//buttons, about and controls window
		sf::Clock cooldownClock;												//for arrows delay
		sf::Vector2u sizeVector;												//in case of window size change
		sf::RenderWindow &window;												//the window
public:
		StartMenu(sf::RenderWindow &_window);					

		~StartMenu();

		void run();				//main procedure 

		void drawAbout();		//about window

		void drawControls();	//controls window
	};