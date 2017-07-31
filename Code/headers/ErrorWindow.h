#pragma once

#include <SFML/Graphics.hpp>

class ErrorWindow {
	sf::Texture *errorTexture;	//textures
	sf::Sprite *error;			//

public:
	ErrorWindow(int num);	//number of error

	~ErrorWindow();

	void run(sf::RenderWindow &window);	//main function
	};