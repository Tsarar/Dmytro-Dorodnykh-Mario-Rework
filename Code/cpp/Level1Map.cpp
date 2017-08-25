#include "../headers/Level1Map.h"

	Level1Map::Level1Map(sf::RenderWindow &window, bool showMenu) : LevelMap(window) {
		
		setNumOfLevel(1);				//default values
		W=166;						//
		coinsToWin=11;					//
		Mario->setWinCondition(coinsToWin);		//
		
		tileSet.loadFromFile("images/Mario_tileset.png");	//loading textures
		Mario->setSprite(tileSet);				//

		colorX=107;		//setting color
		colorY=140;		//
		colorZ=255;		//

		try {
			reloadMap();	//
		}
		catch (...) {
			throw;
		}
		
		mushroom = new Mushroom(*this,tileSet,53,13);	//mushroom generation between the pipes

		tile.setTexture(tileSet);			//for drawing level		
		
		jumpBuff->loadFromFile("sounds/Jump.ogg");	//jump sound
		jump->setBuffer(*jumpBuff);			//

		smashBuffer = new sf::SoundBuffer;		//smash sound
		smashBuffer->loadFromFile("sounds/Smash.ogg");	//
		smashSound = new sf::Sound;			//
		smashSound->setBuffer(*smashBuffer);		//

		pipeBuffer = new sf::SoundBuffer;		//pipe sound
		pipeBuffer->loadFromFile("sounds/Pipe.ogg");	//
		pipeSound = new sf::Sound;			//
		pipeSound->setBuffer(*pipeBuffer);		//

		music->openFromFile("sounds/Mario_Theme.ogg");	//background music
		music->setLoop(true);				//endless
		music->play();					//

		pauseTexture->loadFromFile("images/Pause.png");	//
		pauseSprite->setTexture(*pauseTexture);		//
		pauseSprite->setPosition(150,100);		//

		winTexture->loadFromFile("images/Win_Level1.png");	//win
		winSprite->setTexture(*winTexture);			//

		Menu = new StartMenu(window);				//starting menu
	
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
		upsText.setString("");
		upsText.setColor(sf::Color::White);	//that will show how many main cycles are made per nearly 1 sec
		upsText.setPosition(10,50);		//700 and more is cool, 600 is pretty good, 300 is lagging but ok (it happens in fullscreen)
		upsText.setString("ups:");		//it changes every 0.1 sec, so result is prediction

		rightConst = getW()*16-200;		//to avoid math in cycle
		setOffsetX(48);				//to hide garbage

		clockForDown = new sf::Clock;		//clock for going deeper
		goDeep=false;				//are we going deeper?

		Mario->teleport(11,5);			//placing mario

		if (showMenu) Menu->run();		//starting from menu
	};

	Level1Map::Level1Map(const Level1Map &_level1map) : LevelMap(_level1map.window)  {
		W=_level1map.getW();								//copy everything
		offsetX=_level1map.offsetX;							//
		offsetY=_level1map.offsetY; 							//
		for (int i=0;i<_level1map.H;i++)						//
			for (int j=0;j<_level1map.W;j++) TileMap[i]=_level1map.TileMap[i];	// 
		};

	Level1Map::~Level1Map(){
			delete clockForDown;	//freeing memory
			delete Menu;		//
			delete smashSound;	//
			delete smashBuffer;	//
			delete pipeSound;	//
			delete pipeBuffer;	//
			delete mushroom;	//		
		};

	inline void Level1Map::drawAll() {
			if (!goDeep) window.draw(Mario->getSprite());		//draw mario
			window.draw(Mario->getHearts());			//draw mario's lives
			window.draw(mushroom->getSprite());			//draw mushroom
			window.draw(coinText);					//coin counter and coin
			window.draw(*coin);					//
			if (saveClock->getElapsedTime().asSeconds()<3 && clockPause->getElapsedTime().asSeconds()>3.3)	//save text
				window.draw(*saveText);				//the text is displayed only 3 seconds after a pause
			if (pause && !goDeep) window.draw(*pauseSprite);	//pause
			if (Mario->playerIsWon()) window.draw(*winSprite);	//win
		};

	inline void Level1Map::drawTiles() {
			for (int i=0; i<getH(); i++)							//height cycle
			for (int j=int(getOffsetX()*0.063)-3; j<int(getOffsetX()*0.063)+28; j++)	//wight cycle (this const is optimal)
			  {	switch (getTileMap(i,j)) {
						case 'P': tile.setTextureRect( sf::IntRect(96,112,16,16) );		break;	//floor
						case 'k': tile.setTextureRect( sf::IntRect(144,112,16,16) );		break;	//block
						case 'c': tile.setTextureRect( sf::IntRect(128,112,16,16) );		break;	//block-bonus
						case 'e': tile.setTextureRect( sf::IntRect(128,128,16,16) );		break;	//empty block-bonus
						case 't': tile.setTextureRect( sf::IntRect(0,48,32,48) );		break;	//pipe with secret
						case 'T': tile.setTextureRect( sf::IntRect(0,48,32,48) );		break;	//pipe
						case 'b': tile.setTextureRect( sf::IntRect(0,141,48,19) );		break;	//lil hill
						case 'G': tile.setTextureRect( sf::IntRect(144,221,80,35) );		break;	//hill
						case 'd': tile.setTextureRect( sf::IntRect(0,96,64,16) );		break;	//grass
						case 'w': tile.setTextureRect( sf::IntRect(64,232,32,24) );		break;	//lil cloud
						case 'r': tile.setTextureRect( sf::IntRect(112,112,16,16) );		break;	//stairs
						case 'H': tile.setTextureRect( sf::IntRect(240,192,16,16) );		break;	//teleport
						case 'U': tile.setTextureRect( sf::IntRect(0,16,16,16) );		break;	//unicorn
						case 'u': tile.setTextureRect( sf::IntRect(16,16,-16,16) );		break;	//reverse unicorn
						case 'W': tile.setTextureRect( sf::IntRect(240,176,16,16) );		break;	//water
						case 'C': tile.setTextureRect( sf::IntRect(240,208,16,16) );		break;	//coin
						case ' ': continue;								//air
						case '0': continue;								//invisible wall
					}
				tile.setPosition(j*16-getOffsetX(), float(i*16)); 	//set the position of block, y coord doesn't matter
		        window.draw(tile);						//draw textures
		     }
		};

	int Level1Map::update() {
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
				bufNum=eventHandling();				//handling key events
				if (!(Mario->alive())) playerDeath(time);	//death check
			}							//
			catch (...) {						//
				throw;						//
			}							//

			if (bufNum!=0) return bufNum;
			pauseEvent();

			basicControls();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) if (!pause) if (Mario->onTube() && Mario->playerIsWon()) 
				{
					goDeep=true;					//we are going down
					pause=true;					//stopping enemies
					clockForDown->restart();			//this is needed for animation
					pauseSprite->setColor(sf::Color::Transparent);	//pause shouldn't bother us
					music->pause();					//no music
					pipeSound->play();				//but sound
				}
			
			if (!pause) {
					Mario->update(time);		//update characters
					mushroom->update(time);		//
				}
			else if (goDeep) {				//going down
					Mario->updateAxisY(time);	//
					if (clockForDown->getElapsedTime().asSeconds()<=float(1.5)) Mario->setDy(Mario->getDy()+time*0.00001);	//mario disappears
					window.draw(Mario->getSprite());		//draw mario behind everything

					if (clockForDown->getElapsedTime().asSeconds()>=2) return 2;
				}

			if (Mario->getRect().intersects(mushroom->getRect()) )		//collision with mushroom
			 {							
				if (Mario->alive())					//
					if (mushroom->getLife()) {			//if enemy alive
						 if (Mario->getDy()>0) {
							 mushroom->setDx(0);		//mario can smash him or
							 Mario->setDy(-0.2);		//
							 smashSound->play();		//
							 mushroom->setLife(false);	//
						 }	
					else Mario->hurt();		//mario takes damage
					}
			 }

			changeOffsets();

			coins.str(" ");					//change coins counter
			coins << Mario->getCoins() << "/11";		//
			coinText.setString( coins.str() );		//

			drawTiles();	//draw level
			drawAll();	//

			if (showUps) {
					counter++;															//ups counter
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

	void Level1Map::reloadLevel() {
			mushroom->setLife(true);		//Resurrection of mushroom
			mushroom->teleport(53,13);		//
			mushroom->setDx(0.05);			//
			Mario->setLives(4);			//default values
			Mario->setBlinking(false);		//
			Mario->setTeleported(false);		//
			Mario->setIsWon(false);			//
			Mario->hurt();				//
			Mario->setDx(0);			//
			Mario->setDy(0);			//
			Mario->setCoins(0);			//
			setOffsetY(0);				//level and music reload
			setOffsetX(48);				//to avoid trash on the left			
			music->play();				//
			Mario->teleport(11,5);			//mario spawn

			try {
				reloadMap();			//
			}
			catch (...) {
				throw;
			}
		};

	inline void Level1Map::pauseEvent(){
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))  //pause
					{
					if (!goDeep) {
						timerPause = clockPause->getElapsedTime().asSeconds();	//
						if (timerPause > 0.2) {			//0.2 sec delay
								pause=!pause;		//stop or resume
								clockPause->restart();	//zeroing clock
							};			
						}
					};
		}

	void Level1Map::killEnemies() {
			mushroom->setLife(false);
			mushroom->setDx(0);
		};

	bool Level1Map::isEnemiesAlive() const
		{ return (mushroom->getLife()) ? true : false; }
