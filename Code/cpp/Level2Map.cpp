#include "../headers/Level2Map.h"

	Level2Map::Level2Map(sf::RenderWindow &window) : LevelMap(window) {
		
		setNumOfLevel(2);				//default values
		W=166;						//
		coinsToWin=19;					//
		Mario->setWinCondition(coinsToWin);		//

		tileSet.loadFromFile("images/Mario_tileset.png");	//loading textures
		Mario->setSprite(tileSet);
		
		colorX=66;		//setting color
		colorY=63;		//
		colorZ=146;		//
		
		try {
			reloadMap();	//loading tiles
		}
		catch (...) {
			throw;
		}

		slime1 = new Slime(*this,tileSet,73,13);		//slimes generation
		slime2 = new Slime(*this,tileSet,93,13);		//
		slime3 = new Slime(*this,tileSet,113,13);		//

		tile.setTexture(tileSet);				//for drawing level		
		
		jumpBuff->loadFromFile("sounds/Jump.ogg");		//jump sound
		jump->setBuffer(*jumpBuff);				//

		smashBuffer = new sf::SoundBuffer;			//smash sound
		smashBuffer->loadFromFile("sounds/Smash.ogg");		//
		smashSound = new sf::Sound;				//
		smashSound->setBuffer(*smashBuffer);			//

		music->openFromFile("sounds/Mario_Theme.ogg");		//background music
		music->setLoop(true);					//endless
		music->play();						//

		pauseTexture->loadFromFile("images/Pause.png");		//
		pauseSprite->setTexture(*pauseTexture);			//
		pauseSprite->setPosition(150,100);			//

		winTexture->loadFromFile("images/Win_Level2.png");	//win
		winSprite->setTexture(*winTexture);			//

		font.loadFromFile("fonts/sansation.ttf");		//coins counter
		
		saveText->setString("Game has been saved");		//placing save text
		saveText->setCharacterSize(14);				//
		saveText->setFont(font);				//
		saveText->setColor(sf::Color::White);			//
		saveText->setPosition(30,223);				//
		
		coinText.setString("");					//placing coins text
		coinText.setCharacterSize(14);				//
		coinText.setFont(font);					//
		coinText.setColor(sf::Color::White);			//
		coinText.setPosition(30,30);				//
														
		coin->setPosition(10,31);				//placing sprite
		coin->setTexture(tileSet);				//choosing sprite
		coin->setTextureRect( sf::IntRect(240,208,16,16) );	//

		counter = 0;				//
		upsText.setFont(font);			//setting text for ups
		upsText.setCharacterSize(14);		//
		upsText.setString("");			//
		upsText.setColor(sf::Color::White);	//that will show how many main cycles are made per nearly 1 sec
		upsText.setPosition(10,50);		//700 and more is cool, 600 is pretty good, 300 is lagging but ok (it happens in fullscreen)
		upsText.setString("ups:");		//it changes every 0.1 sec, so result is prediction

		rightConst = getW()*16-200;		//to avoid math in cycle
		setOffsetX(48);				//to hide garbage

		Mario->teleport(11,5);			//placing mario
	};

	Level2Map::Level2Map(const Level2Map &_level2map) : LevelMap(_level2map.window)  {
		W=_level2map.getW();								//copy everything
		offsetX=_level2map.offsetX;							//
		offsetY=_level2map.offsetY; 							//
		for (int i=0;i<_level2map.H;i++)						//
			for (int j=0;j<_level2map.W;j++) TileMap[i]=_level2map.TileMap[i];	// 
		};

	Level2Map::~Level2Map() {
			delete smashSound;	//freeing memory
			delete smashBuffer;	//
			delete slime3;		//
			delete slime2;		//
			delete slime1;		//
		};

	inline void Level2Map::drawAll() {
			window.draw(Mario->getSprite());	//draw mario
			window.draw(Mario->getHearts());	//     mario's lives
			window.draw(slime1->getSprite());	//     slime1
			window.draw(slime2->getSprite());	//     slime2
			window.draw(slime3->getSprite());	//     slime3
			window.draw(coinText);			//     coin counter and coin
			window.draw(*coin);			//
			if (saveClock->getElapsedTime().asSeconds()<3 && clockPause->getElapsedTime().asSeconds()>3.3)	//save text
				window.draw(*saveText);																		//the text is displayed only 3 seconds after a pause
			if (pause) window.draw(*pauseSprite);			//pause
			if (Mario->playerIsWon()) window.draw(*winSprite);	//win
		};

	inline void Level2Map::drawTiles() {
		for (int i=0; i<getH(); i++)													//height cycle
			for (int j=int(getOffsetX()*0.063)-3; j<int(getOffsetX()*0.063+28); j++)	//wight cycle (this const is optimal)
			  {	switch (getTileMap(i,j)) {
						case 'P': tile.setTextureRect( sf::IntRect(80,144,16,16) );		break;	//dirt
						case 'g': tile.setTextureRect( sf::IntRect(64,80,16,16) );		break;	//grass
						case 'k': tile.setTextureRect( sf::IntRect(48,112,16,16) );		break;	//house block
						case 'c': tile.setTextureRect( sf::IntRect(128,112,16,16) );		break;	//block-bonus
						case 'e': tile.setTextureRect( sf::IntRect(128,128,16,16) );		break;	//empty block-bonus
						case 't': tile.setTextureRect( sf::IntRect(64,128,16,16) );		break;	//temple
						case 'T': tile.setTextureRect( sf::IntRect(48,128,16,16) );		break;	//temple 2
						case 'r': tile.setTextureRect( sf::IntRect(48,144,16,16) );		break;	//block
						case 'p': tile.setTextureRect( sf::IntRect(80,96,16,16) );		break;	//platform
						case 'b': tile.setTextureRect( sf::IntRect(80,112,16,16) );		break;	//column
						case 'i': tile.setTextureRect( sf::IntRect(80,112,16,16) );		break;	//solid column
						case 'j': tile.setTextureRect( sf::IntRect(64,112,16,16) );		break;	//column with platform
						case 'f': tile.setTextureRect( sf::IntRect(64,96,16,16) );		break;	//fence
						case 'L': tile.setTextureRect( sf::IntRect(80,128,16,16) );		break;	//ladder
						case 'W': tile.setTextureRect( sf::IntRect(240,160,16,16) );		break;	//water
						case 'w': tile.setTextureRect( sf::IntRect(224,160,16,16) );		break;	//deep water
						case 'C': tile.setTextureRect( sf::IntRect(240,208,16,16) );		break;	//coin
						case ' ': continue;								//air
						case '0': continue;								//invisible wall
					}
				tile.setPosition(j*16-getOffsetX(), float(i*16)); 	//set the position of block, y coord doesn't matter
		        window.draw(tile);						//draw textures
		     }
		};

	int Level2Map::update() {
		while (window.isOpen())	{
			window.clear(sf::Color(int(colorX),int(colorY),int(colorZ)));	//clear current frame

			time = float(clock->getElapsedTime().asMicroseconds())/500;	//get time and set speed (can be adjusted)
			clock->restart();						//clock restart

			if (time>20) time=20;		//in case of bad optimization sometimes 
							//(when the objects are initialized or in case of fullscreen)
							//program takes a lot of processor time
							//this line sets limit, that helps avoiding crushes

			static int bufNum;

			try {							//
				if (!(Mario->alive())) playerDeath(time);	//handling key events
				bufNum=eventHandling();				//death check
			}							//
			catch (...) {						//
				throw;						//
			}							//

			if (bufNum!=0) return bufNum;
			pauseEvent();

			basicControls();
			
			if (!pause) {
					Mario->update(time);	//update characters
					slime1->update(time);	//
					slime2->update(time);	//
					slime3->update(time);	//
				};

			if (Mario->getRect().intersects(slime1->getRect())) enemyCollision(*slime1);	//collision with slimes
			if (Mario->getRect().intersects(slime2->getRect())) enemyCollision(*slime2);	//
			if (Mario->getRect().intersects(slime3->getRect())) enemyCollision(*slime3);	//

			changeOffsets();
			if (Mario->playerIsWon()) if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { window.close(); return 0; }	//end

			coins.str(" ");					//change coins counter
			coins << Mario->getCoins() << "/19";		//
			coinText.setString( coins.str() );		//

			drawTiles();	//draw level
			drawAll();	//

			if (showUps) {
					counter++;									//ups counter
					if (upsClock.getElapsedTime().asSeconds()>=0.1)					//every second it
						{ if (counter>60) upsText.setColor(sf::Color::Green);			//colors the text
							else if (counter>30) upsText.setColor(sf::Color::Yellow);	//
							else upsText.setColor(sf::Color::Red);				//

					ups.str("");						//
					ups << "ups:" << counter*10 << '\n'; counter=0;		//
					upsClock.restart();					//
					upsText.setString( ups.str() ); }			//and changes ups (updates per second)
					window.draw(upsText);					//
				};

			window.display();
		};
		return -1;	//to avoid warning and in case of some magic impossible stuff
	};

	void Level2Map::reloadLevel() {
			slime1->setLife(true);		//Resurrection of slimes
			slime1->teleport(73,13);	//
			slime1->setDx(0.07);		//
			slime2->setLife(true);		//
			slime2->teleport(93,13);	//
			slime2->setDx(0.07);		//
			slime3->setLife(true);		//
			slime3->teleport(113,13);	//
			slime3->setDx(0.07);		//
			Mario->setLives(4);		//default values
			Mario->setBlinking(false);	//
			Mario->setTeleported(false);	//
			Mario->setIsWon(false);		//
			Mario->teleport(11,5);		//
			Mario->hurt();			//
			Mario->setDx(0);		//
			Mario->setDy(0);		//
			Mario->setCoins(0);		//
			setOffsetY(0);			//level and music reload
			setOffsetX(48);			//
			music->play();			//
			try {
				reloadMap();		//
			}
			catch (...) {
				throw;
			}
			
		};

	inline void Level2Map::pauseEvent(){
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))  //pause
					{
						timerPause = clockPause->getElapsedTime().asSeconds();	//
						if (timerPause > 0.2) {				//0.2 sec delay
								pause=!pause;			//stop or resume
								clockPause->restart();		//zeroing clock
							}
					}
		}

	inline void Level2Map::enemyCollision(Entity &slime) {
			if (Mario->alive())				//
				if (slime.getLife()) {			//if enemy alive
					if (Mario->getDy()>0) {
						slime.setDx(0);		//Mario can smash it and take damage or
						Mario->setDy(-0.2);	//
						Mario->hurt();		//
						smashSound->play();	//
						slime.setLife(false);	//
					}
					else Mario->hurt();		//mario takes damage
					}
		};

	void Level2Map::killEnemies() {
			slime1->setLife(false);
			slime1->setDx(0);
			slime2->setLife(false);
			slime2->setDx(0);
			slime3->setLife(false);
			slime3->setDx(0);
		};

	bool Level2Map::isEnemiesAlive() const 
		 { return (slime1->getLife() || slime2->getLife() || slime3->getLife()) ? true : false; };
