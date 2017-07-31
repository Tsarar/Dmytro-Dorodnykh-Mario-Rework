#define _CRT_SECURE_NO_WARNINGS	//to disable C4996 warning

#include "../headers/LevelMap.h"
#include "../headers/ErrorWindow.h"
#include "../headers/SaveWindow.h"

	void LevelMap::reloadMap() {
			std::ostringstream currentLevel;
			currentLevel << "levels/Level" << *numberOfLevel << ".txt";

			std::ifstream *fileWithLevel;										//get our level from file
			fileWithLevel = new std::ifstream(currentLevel.str());				//
			if (!(fileWithLevel->good()))	{									//in case problems
						ErrorWindow *error = new ErrorWindow(1);				//we launch error
						error->run(window);										//
					}															//
			for (int i=0;i<H;i++) { std::getline(*fileWithLevel,TileMap[i]); }	//
			fileWithLevel->close();			
		};

	LevelMap::LevelMap(sf::RenderWindow &_window) : window(_window), offsetX(0), offsetY(0) {
			numberOfLevel = new int;			//current level
			jumpBuff = new sf::SoundBuffer;		//jump sound
			jump = new sf::Sound;				//
			music = new sf::Music;				//background music
			clock = new sf::Clock;				//main clock	
			clockPause = new sf::Clock;			//pause clock
			timerPause = new float;				//
			pause = new bool;					//pause	
			pauseTexture = new sf::Texture;		//
			pauseSprite = new sf::Sprite;		//
			winTexture = new sf::Texture;		//win
			winSprite = new sf::Sprite;			//
			DMenu = new DeathMenu;				//death menu
			coin = new sf::Sprite;				//coin at the corner
			showUps = new bool;					//show ups?
			coinsToWin = new int;				//amount of coins to win the level
			saveText = new sf::Text;			//save message
			saveClock = new sf::Clock;			//
			realOffset = new float;				//real offset for save
			Mario = new Player(*this);			//Mario

			*pause = false;						//pause
			*showUps = true;					//ups
		};

	LevelMap::~LevelMap() {
			delete Mario;			//freeing memory
			delete realOffset;		//
			delete saveClock;		//
			delete saveText;		//
			delete coinsToWin;		//
			delete showUps;			//
			delete coin;			//			
			delete DMenu;			//
			delete winSprite;		//
			delete winTexture;		//
			delete pauseSprite;		//
			delete pauseTexture;	//
			delete pause;			//
			delete timerPause;		//
			delete clockPause;		//
			delete clock;			//
			delete music;			//
			delete jump;			//
			delete jumpBuff;		//
			delete numberOfLevel;	//
		};

	inline void LevelMap::basicControls() {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		Mario->setDx(-0.1);					//player goes left
       		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	Mario->setDx(0.1);					//or goes right
    		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  if (Mario->getOnGround()) if (!(*pause)) if (Mario->canJump()) { Mario->setDy(-0.27); Mario->setOnGround(false); Mario->spriteUpdate(); if (!jump->getStatus()) jump->play();}		//jump of he is not in air
		};

	inline int LevelMap::eventHandling(){
			static sf::Event event;					//event handling
			while (window.pollEvent(event))			//
			{											
			    if (event.type == sf::Event::Closed) window.close();					//close the window

				if (event.type == sf::Event::KeyPressed) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
					{
						*timerPause = clockPause->getElapsedTime().asSeconds();			//
						if (*timerPause > 0.2) {										//0.2 sec delay
								(music->getStatus()) ? music->stop() : music->play(); 	//stop or resume mucis
								clockPause->restart();									//zeroing clock
							};				
					};

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
					if (Mario->playerIsWon())
						{
							reloadLevel();		//reload level
						}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) (*showUps) ? *showUps=false : *showUps=true;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
					if (!(*pause)) {
						SaveWindow save(window, *this);
						int buf=save.run(window,1);
					}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) 
					if (!(*pause)) {
						SaveWindow save(window, *this);
						int buf = save.run(window,2);
						if (buf!=0) return buf;
					}
				}
			}
			return 0;
		};

	inline void LevelMap::pauseEvent(){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))  //pause
					{
						*timerPause = clockPause->getElapsedTime().asSeconds();	//
						if (*timerPause > 0.2) {								//0.2 sec delay
								(!(*pause))  ? *pause=true : *pause=false;		//stop or resume
								clockPause->restart();							//zeroing clock
							}
					}
		};

	inline void LevelMap::changeOffsets() {
			if (Mario->getRect().left>248 && Mario->getRect().left<(rightConst)) setOffsetX(Mario->getRect().left - 200); //borders that don't allows to seeempty tiles or garbage
			*realOffset=Mario->getRect().left;	//for saves
			setOffsetY(Mario->getRect().top);	//change y position too, through it don't have any influence on camera, it is needed for death animation
		};

	void LevelMap::playerDeath(float time){
		if (!(*pause)) {
				*pause=true;									//pause
				pauseSprite->setColor(sf::Color::Transparent);	//
				clockPause->restart();							//
				
				music->stop();						//preparing to die
				sf::Clock deathClock;				//
				Mario->death();						//
				bool stopGoingHigher=false;			//variable for going up
				while (true) {
					Mario->updateAxisY(time);										//player moves only up or down
					window.clear(sf::Color(int(colorX),int(colorY),int(colorZ)));	//clear current frame
					drawTiles();													//draw his movement
					drawAll();														//
					window.display();												//
					setOffsetY(Mario->getRect().top);								//
					if (deathClock.getElapsedTime().asSeconds()>=float(0.15))		//delay
						{
							(!stopGoingHigher) ? Mario->setDy(Mario->getDy()-0.00016) : Mario->setDy(Mario->getDy()+0.001);	//go up, then down
							if (offsetY<=90) stopGoingHigher=true;		//changing direction
							if (offsetY>=1000 && deathClock.getElapsedTime().asSeconds()>=float(2.7)) { break; }			//stop the animation
						};
					};
				if (DMenu->run(window)) {						//if mario died ask about restart 
						reloadLevel();							//reload level
						*pause=false;							//
						pauseSprite->setColor(sf::Color::White);//
					}											//
				else window.close();							//exit
			};
		};

	void LevelMap::saveToFile(int numOfSave) const {

		time_t seconds = std::time(NULL);		//getting system time to save in file
		tm *timeinfo = localtime(&seconds);		//
		
		std::ostringstream currentSave;							//write our save to file
		currentSave << "saves/Save" << numOfSave << ".txt";		//
		std::ofstream *fileWithLevel;							//
		fileWithLevel = new std::ofstream(currentSave.str());	//

		if (!(fileWithLevel->good())) {						//if problems with file
				ErrorWindow *error = new ErrorWindow(3);	//we launch error
				error->run(window);							//
			}	
		 
		*fileWithLevel << getNumberOfLevel() << " " << Mario->getLives()<< " " << Mario->getCoins() << " " << getMaxCoins() << " ";	//writing info
		if (isEnemiesAlive()) *fileWithLevel << 1 << " "; else *fileWithLevel << 0 << " ";											//
		*fileWithLevel << getOffsetX() << " " << getOffsetY() << " " << getW() << " ";					//
		*fileWithLevel << timeinfo->tm_mon+1 << " " << timeinfo->tm_mday << " " << timeinfo->tm_year+1900 << " " << timeinfo->tm_hour << " " << timeinfo->tm_min << " ";
		*fileWithLevel << getRealOffset() << std::endl;

		for (int i=0;i<getH();i++) {										//writing map
			for (int j=0;j<getW();j++) *fileWithLevel << getTileMap(i,j);	//
				*fileWithLevel << std::endl;								//
			}																//

		fileWithLevel->close();	//end

		saveClock->restart();
	};

	void LevelMap::loadFromFile(int numOfSave) {
			std::ostringstream currentSave;											//get our save from file
			currentSave << "saves/Save" << numOfSave << ".txt";						//
			std::ifstream *fileWithLevel = new std::ifstream(currentSave.str());	//

			if (!(fileWithLevel->good())) {							//if problems with file
						ErrorWindow *error = new ErrorWindow(3);	//we launch error
						error->run(window);							//
					}

			int numOfLvl, lives, coins, maxCoins, bufW;		//reading info
			bool isEnemiesAlive;							//
			float oX, oY, rOX;								//
			int month, day, year, hour, min;				//
			*fileWithLevel >> numOfLvl >> lives >> coins >> maxCoins >> isEnemiesAlive >> oX >> oY >> bufW >> month >> day >> year >> hour >> min >> rOX;//
			Mario->setLives(lives);							//setting info
			Mario->setCoins(coins);							//
			Mario->heartsChange();							//
			Mario->teleport(int((rOX)/16), int(oY/16));		//
			if (Mario->getCoins()>=maxCoins) Mario->setIsWon(true);//
			if (!isEnemiesAlive) this->killEnemies();		//
			setNumOfLevel(numOfLvl);						//
			setMaxCoins(maxCoins);							//
			setOffsetX(oX);									//
			setOffsetY(oY);									//
			setW(bufW);										//
			
			char bufTile;									//reading map
			fileWithLevel->read(&bufTile,1);				//skipping first '\n'
			for (int i=0;i<getH();i++) {																//
				for (int j=0;j<getW();j++) { fileWithLevel->read(&bufTile,1); setTileMap(i,j,bufTile); }//getting info
				fileWithLevel->read(&bufTile,1);														//skipping '\n'
				}																						//

		};