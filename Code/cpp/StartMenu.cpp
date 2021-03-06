#include "../headers/StartMenu.h"

	StartMenu::StartMenu(sf::RenderWindow &_window) : window(_window) {

				menuTexture1.loadFromFile("images/NewGame.png");	//buttons
				menuTexture2.loadFromFile("images/AboutButton.png");	//
				menuTexture3.loadFromFile("images/ControlsButton.png");	//
				menuTexture4.loadFromFile("images/Exit.png");		//
				aboutTexture.loadFromFile("images/About.png");		//
				controlsTexture.loadFromFile("images/Controls.png");	//
				menu1.setTexture(menuTexture1);				//rectangles
				menu2.setTexture(menuTexture2);				//
				menu3.setTexture(menuTexture3);				//
				menu4.setTexture(menuTexture4);				//
				about.setTexture(aboutTexture);				//
				controls.setTexture(controlsTexture);			//

				stand=0;						//menu starts as zero
				menuNum=0;						//
				menu1.setPosition(100,30);				//standart positions
				menu2.setPosition(100,80);				//
				menu3.setPosition(100,130);				//
				menu4.setPosition(100,180);				//
			};

	StartMenu::~StartMenu() {};

	void StartMenu::run() {
			window.setTitle("Start Menu");
			while(window.isOpen()) {		//main cycle
					static sf::Event event;
					while (window.pollEvent(event))
						{
							if (event.type == sf::Event::Closed) { window.close(); }  //event handling
						};

					(menuNum==1) ? menu1.setColor(sf::Color::Yellow) : menu1.setColor(sf::Color::White);	//activating buttons
					(menuNum==2) ? menu2.setColor(sf::Color::Yellow) : menu2.setColor(sf::Color::White);	//
					(menuNum==3) ? menu3.setColor(sf::Color::Yellow) : menu3.setColor(sf::Color::White);	//
					(menuNum==4) ? menu4.setColor(sf::Color::Yellow) : menu4.setColor(sf::Color::White);	//

					menuNum=stand;				//current button for arrows
					
					window.clear(sf::Color(100,100,100));	//clearing current frame

					sizeVector = window.getSize();																																	//if somebody	
					if (sf::IntRect(sizeVector.x/4,int(sizeVector.y/8.3333),int(sizeVector.x/2.2),sizeVector.y/6).contains(sf::Mouse::getPosition(window))) {stand=0; menuNum=1;}	//will decide	//default:100,30,181,42
					if (sf::IntRect(sizeVector.x/4,int(sizeVector.y/3.1250),int(sizeVector.x/2.2),sizeVector.y/6).contains(sf::Mouse::getPosition(window))) {stand=0; menuNum=2;}	//to strech	//default:100,80,181,42
					if (sf::IntRect(sizeVector.x/4,int(sizeVector.y/1.9231),int(sizeVector.x/2.2),sizeVector.y/6).contains(sf::Mouse::getPosition(window))) {stand=0; menuNum=3;}	//the window	//default:100,130,181,42
					if (sf::IntRect(sizeVector.x/4,int(sizeVector.y/1.3888),int(sizeVector.x/2.2),sizeVector.y/6).contains(sf::Mouse::getPosition(window))) {stand=0; menuNum=4;}	//the window	//default:100,180,181,42
					
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
						sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
						//onClick or ENTER event
						if (menuNum<2) { window.setTitle("Mario!"); break; }	//start the game
						else if (menuNum==2) drawAbout();			//about
						else if (menuNum==3) drawControls();			//controls
						else if (menuNum==4) window.close();			//exit
					 }

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {		//arrows
						if (cooldownClock.getElapsedTime().asSeconds() > 0.15){	//delay
							++stand;			//active button goes down
							if (stand>4) stand=1;		//cycling
							cooldownClock.restart();	//
						};
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {		//arrows
						if (cooldownClock.getElapsedTime().asSeconds() > 0.15){	//delay
							--stand;				//active button goes up
							if (stand<1) stand=4;			//cycling
							cooldownClock.restart();		//
						};
					}
	   
					window.draw(menu1);			//display
					window.draw(menu2);			//
					window.draw(menu3);			//
					window.draw(menu4);			//
										//
					window.display();			//
				}
			};

	void StartMenu::drawAbout() {
		window.setTitle("About");
		while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && window.isOpen()) {
			window.clear(sf::Color(100,100,100));							//clearing current frame
			window.draw(about);									//draw menu
			static sf::Event event;
			while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed) window.close();		//event handling
					};
			window.display();
			};
		window.setTitle("Start Menu");
		};

	void StartMenu::drawControls() {
		window.setTitle("Controls");
		while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && window.isOpen())  {
			window.clear(sf::Color(100,100,100));							//clearing current frame
			window.draw(controls);									//draw menu
			static sf::Event event;
			while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed) window.close();		//event handling
					};
			window.display();
			};
		window.setTitle("Start Menu");
		};
