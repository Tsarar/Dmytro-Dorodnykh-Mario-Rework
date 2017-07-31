#include "../headers/SaveWindow.h"
#include "../headers/ErrorWindow.h"

	SaveWindow::SaveWindow(sf::RenderWindow &_window, LevelMap &map) : window(_window), map(map) {
		saveTexture = new sf::Texture;			//heap usage
		escTexture = new sf::Texture;			//
		save1 = new sf::Sprite;					//
		save2 = new sf::Sprite;					//
		save3 = new sf::Sprite;					//
		esc = new sf::Sprite;					//
		stand = new int;						//
		menuNum = new int;						//
		cooldownClock = new sf::Clock;			//
		sizeVector = new sf::Vector2u;			//

		saveFile1 = new Save(window,1);		//save files
		saveFile2 = new Save(window,2);		//
		saveFile3 = new Save(window,3);		//
												
		saveTexture->loadFromFile("images/SaveWindow.png"); //loading textures and setting sprites
		escTexture->loadFromFile("images/Esctoclose.png");	//
		save1->setTexture(*saveTexture);					//
		save2->setTexture(*saveTexture);					//
		save3->setTexture(*saveTexture);					//
		esc->setTexture(*escTexture);						//

		initializeSave(1, saveFile1);		//load save 1
		initializeSave(2, saveFile2);		//     save 2
		initializeSave(3, saveFile3);		//     save 3

		*stand=0;				//menu starts as zero
		*menuNum=0;				//

		save1->setPosition(40,14);		//standart positions
		save2->setPosition(40,84);		//
		save3->setPosition(40,154);		//
		esc->setPosition(20,204);		//
	};

	SaveWindow::~SaveWindow() {
		delete saveTexture;
		delete save1;
		delete save2;
		delete save3;
		delete stand;
		delete menuNum;
		delete cooldownClock;
		delete sizeVector;
		delete saveFile1;
		delete saveFile2;
		delete saveFile3;
	};

	int SaveWindow::run(sf::RenderWindow &window, int mode) {	//1 means save, else load
		while (window.isOpen()) {
			static sf::Event event;
			while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed) window.close();  //event handling
				};

			(*menuNum==1) ? save1->setColor(sf::Color::Yellow) : save1->setColor(sf::Color::White);//activating saves
			(*menuNum==2) ? save2->setColor(sf::Color::Yellow) : save2->setColor(sf::Color::White);//
			(*menuNum==3) ? save3->setColor(sf::Color::Yellow) : save3->setColor(sf::Color::White);//

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) break;	//back to game

			*menuNum=*stand;				//current save for arrows

			*sizeVector = window.getSize();																																	//if somebody	
			if (sf::IntRect(sizeVector->x/10,int(sizeVector->y/17.857),int(sizeVector->x/1.25),int(sizeVector->y/4.4)).contains(sf::Mouse::getPosition(window))) {*stand=0; *menuNum=1;}	//will decide	//default:40,20,320,57
			if (sf::IntRect(sizeVector->x/10,int(sizeVector->y/2.9761),int(sizeVector->x/1.25),int(sizeVector->y/4.4)).contains(sf::Mouse::getPosition(window))) {*stand=0; *menuNum=2;}	//to strech		//default:40,90,320,57
			if (sf::IntRect(sizeVector->x/10,int(sizeVector->y/1.6233),int(sizeVector->x/1.25),int(sizeVector->y/4.4)).contains(sf::Mouse::getPosition(window))) {*stand=0; *menuNum=3;}	//the window	//default:40,160,320,57

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {		//onClick event
				if (*menuNum==1) { if (mode==1) { map.saveToFile(1); break; } else if (!saveFile1->getIsEmpty()) return hashFromFile(1); }	//save1
				if (*menuNum==2) { if (mode==1) { map.saveToFile(2); break; } else if (!saveFile2->getIsEmpty()) return hashFromFile(2); }	//save2
				if (*menuNum==3) { if (mode==1) { map.saveToFile(3); break; } else if (!saveFile3->getIsEmpty()) return hashFromFile(3); }	//save3
			 }

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {	//Enter event
				if (*menuNum==1) { if (mode==1) { map.saveToFile(1); break; } else if (!saveFile1->getIsEmpty()) return hashFromFile(1); }	//save1
				if (*menuNum==2) { if (mode==1) { map.saveToFile(2); break; } else if (!saveFile2->getIsEmpty()) return hashFromFile(2); }	//save2
				if (*menuNum==3) { if (mode==1) { map.saveToFile(3); break; } else if (!saveFile3->getIsEmpty()) return hashFromFile(3); }	//save3
			 }

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {	//arrows
				if (cooldownClock->getElapsedTime().asSeconds() > 0.15){	//delay
					*stand=*stand+1;								//active button goes down
					if (*stand>3) *stand=1;							//cycling
					cooldownClock->restart();
				};
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {	//arrows
				if (cooldownClock->getElapsedTime().asSeconds() > 0.15){	//delay
					*stand=*stand-1;							//active button goes up
					if (*stand<1) *stand=3;						//cycling
					cooldownClock->restart();
				};
			}

			window.clear(sf::Color(100,100,100));	//clearing current frame
			window.draw(*save1);					//draw our save1 background
			window.draw(*save2);					//         save2
			window.draw(*save3);					//         save3
			window.draw(*esc);						//draw our esc message
			saveFile1->draw();						//draw our save 1 info
			saveFile2->draw();						//		   save 2
			saveFile3->draw();						//		   save 3
			window.display();						//
			};
		return 0;
	};

	void SaveWindow::initializeSave(int numOfSave, Save *save){
		std::ostringstream currentSave;											//get our save from file
		currentSave << "saves/Save" << numOfSave << ".txt";						//
		std::ifstream *fileWithLevel = new std::ifstream(currentSave.str());	//

		if (!(fileWithLevel->good())) {							//if problems with file
					ErrorWindow *error = new ErrorWindow(3);	//we launch error
					error->run(window);							//
			}

		int numOfLvl, lives, coins, maxCoins, bufW;	//buffer variables to read info from file
		bool isEnemiesAlive;						//
		float oX, oY;								//
		int month, day, year, hour, min;			//
		if (fileWithLevel->peek() == -1) numOfLvl=0;//if file is empty
		else
		*fileWithLevel >> numOfLvl >> lives >> coins >> maxCoins >> isEnemiesAlive >> oX >> oY >> bufW >> month >> day >> year >> hour >> min;	//reading
		
		if (numOfLvl==0) { save->setAll(0,0,0,0,0,0,0,0); save->setIsEmpty(true); }								//if file is empty
		else { save->setAll(numOfLvl, maxCoins, coins, min, hour, day, month, year); save->setIsEmpty(false); }	//else giving our vars as the parameters to save
	};

	int SaveWindow::hashFromFile(int numOfSave) const {
			std::ostringstream currentSave;											//get our save from file
			currentSave << "saves/Save" << numOfSave << ".txt";						//
			std::ifstream *fileWithLevel = new std::ifstream(currentSave.str());	//

			if (!(fileWithLevel->good())) {							//if problems with file
						ErrorWindow *error = new ErrorWindow(3);	//we launch error
						error->run(window);							//
					}

			int numOfLevel;					//getting number of level
			*fileWithLevel >> numOfLevel;	//

			return numOfLevel*10+numOfSave;	//returning code
											//first num is level, second is a save
		};