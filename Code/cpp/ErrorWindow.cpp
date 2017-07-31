#include "../headers/ErrorWindow.h"

	ErrorWindow::ErrorWindow(int num) {
		errorTexture = new sf::Texture;			//heap usage
		error = new sf::Sprite;				//
												
		switch (num) {															//loading textures
		case 1: errorTexture->loadFromFile("images/ErrorLevel.png"); break;	//level not found error
		case 2: errorTexture->loadFromFile("images/Continue.png"); break;	//to be continued window
		case 3: errorTexture->loadFromFile("images/SaveTroubles.png"); break;	//can't open save file
		default: errorTexture->loadFromFile("images/Error.png"); break;		//unknown error
			}
		error->setTexture(*errorTexture);		//
	};							//
	
	ErrorWindow::~ErrorWindow() {
		delete errorTexture;	//freeing memory
		delete error;		//
	};
	
	void ErrorWindow::run(sf::RenderWindow &window){
		window.setTitle("Ooops...");
		while(window.isOpen()) {
				static sf::Event event;
				while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed) window.close();  //event handling
					};

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();	//exit
				window.clear(sf::Color(100,100,100));					//clearing current frame
				window.draw(*error);							//display our message
				window.display();							//
			};
	};
