#include "../headers/DeathMenu.h"

	DeathMenu::DeathMenu() {

		yesButton.loadFromFile("images/YesButton.png");		//buttons
		noButton.loadFromFile("images/NoButton.png");		//
		textTexture.loadFromFile("images/GameOver.png");	//

		yes.setTexture(yesButton);		//placing sprites
		no.setTexture(noButton);		//
		text.setTexture(textTexture);		//
		yes.setPosition(60,175);		//
		no.setPosition(285,175);		//
		text.setPosition(0,0);			//

		stand=0;				//menu
		menuNum=0;				//
	};
	
	DeathMenu::~DeathMenu() {};

	bool DeathMenu::run(sf::RenderWindow &window) {
		while(window.isOpen()) {	//main cycle
					static sf::Event event;
					while (window.pollEvent(event))
						{
							if (event.type == sf::Event::Closed) window.close();  //event handling
						};

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) if (menuNum<=1) return 1; else return 0;	//event on pressing enter
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return 0;					//and escape

					window.clear(sf::Color(100,100,100));	//clearing current frame

					
					(menuNum==1) ? yes.setColor(sf::Color::Green) : yes.setColor(sf::Color::White);	//clearing color																
					(menuNum==2) ? no.setColor(sf::Color::Red) : no.setColor(sf::Color::White);	//or coloring

					menuNum=stand;				//for arrows interaction

					sizeVector = window.getSize();		//if somebody will decide to scretch

					if (sf::IntRect(int(sizeVector.x/6.6667),int(sizeVector.y/1.4285),int(sizeVector.x/4.5),sizeVector.y/7).contains(sf::Mouse::getPosition(window))) { //default:60,175,90,36
							stand=0;							//reset buttons
							menuNum=1;							//button 'yes'
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return 1;	//restart
						}
					if (sf::IntRect(int(sizeVector.x/1.4035),int(sizeVector.y/1.4285),sizeVector.x/7,sizeVector.y/7).contains(sf::Mouse::getPosition(window))) { //default:285,175,57,36
							stand=0;							//reset buttons
							menuNum=2;							//button 'no'
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return 0; 	//exit
						}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {		//move arrows
						if (cooldownClock.getElapsedTime().asSeconds()>0.15)	//delay
								{					//
									++stand;			//
									if (stand>2) stand=1;		//
									cooldownClock.restart();	//
								}					//
						}							//

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {		//move arrows
						if (cooldownClock.getElapsedTime().asSeconds()>0.15)	//delay
								{					//
									--stand;			//
									if (stand<1) stand=2;		//
									cooldownClock.restart();	//
								}					//
						}							//

					window.draw(yes);			//display
					window.draw(no);			//
					window.draw(text);			//
										//
					window.display();			//

			};
		return 1;	//to avoid warning and in case of some magic impossible stuff
	};
