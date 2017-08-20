#include "../headers/Player.h"

		Player::Player(LevelMap &_map) : map(_map) {	//setting connection between level and player

			livesTexture.loadFromFile("images/Lives.png");		//hearts display
			hearts.setTexture(livesTexture);			//
			hearts.setTextureRect( sf::IntRect(0,0,63,19) );	//
			hearts.setPosition(10,10);				//


			hitBuff.loadFromFile("sounds/Hit.ogg");			//
			coinBuff.loadFromFile("sounds/Coin.ogg");		//
			teleportBuff.loadFromFile("sounds/Teleport.ogg");	//
			unicornBuff.loadFromFile("sounds/Unicorn.ogg");		//
			bonusBuff.loadFromFile("sounds/Bonus.ogg");		//
			deathBuff.loadFromFile("sounds/Death.ogg");		//

			hitSound.setBuffer(hitBuff);				//
			coinSound.setBuffer(coinBuff);				//
			teleportSound.setBuffer(teleportBuff);			//
			unicornSound.setBuffer(unicornBuff);			//
			bonusSound.setBuffer(bonusBuff);			//
			deathSound.setBuffer(deathBuff);			//

			damageTicks = 0;			//for damage ticks
			timeTick = 0;				//
			isBlinking = false;			//
			lives=3;				//default lives
			coins=0;				//default coins
			isHealed=false;				//default healing
			isWon=false;				//default win
			currentLevel=0;				//default level

			dx=dy=float(0.1);			//starting offset
			currentFrame = 0;			//starting from zero frame
			
			isTeleported = false;			// for teleport
			isDownThePlatform = false;		//for platforms
			solidBlocks.insert('t'); solidBlocks.insert('T'); solidBlocks.insert('r'); solidBlocks.insert('e');	//insertion of solid blocks
			solidBlocks.insert('0'); solidBlocks.insert('k'); solidBlocks.insert('P'); solidBlocks.insert('L');	//
			solidBlocks.insert('g');										//
		}																										

		Player::~Player() {};

		void Player::update(float time)	{	//main procedure	
			rect.left += dx * time;		//unbounding mario with a offset variable
			collision(0);			//x coord blocks interaction

			spriteUpdate();

			if (!(isOnGround) && !(isOnLadder)) dy += float(0.0005) * time;	//gravitation
			rect.top += dy * time;						//getting higher or lower
			isOnGround=false;						//for different interactions
			isOnLadder=false;						//
			collision(1);							//y coord blocks interation

			currentFrame += time * float(0.005);			//updating frame without connection to the processor frequency
			if (currentFrame > 3) currentFrame = 0;			//zeroing frame variable for the animation loop

			if (isBlinking) {							//blinking
					timeTick=damageClock.getElapsedTime().asSeconds();	//for a tick delay	
					if (timeTick>0.35) {					//can be easily changed
							if (damageTicks==0 || damageTicks==2 || damageTicks==4) sprite.setColor(sf::Color::Transparent);	//transparent blink
							else sprite.setColor(sf::Color::Red);									//red blink
							++damageTicks;												//counter++
							damageClock.restart();											//zeroing delay
							if (damageTicks==6) { sprite.setColor(sf::Color::White); isBlinking = false; damageTicks = 0; };	//end of blinking
						}
				}
			if (isDownThePlatform) if (platformClock.getElapsedTime().asSeconds()>0.5) isDownThePlatform=false;

			sprite.setPosition(rect.left - map.getOffsetX(), rect.top);		//moving background and setting its position, y coord doesn't matter
			isTeleported=false;							//for tp interations
			isHealed=false;								//
			dx=0;									//standing at one place without hitting buttons
		}

		void Player::collision(int num)	{		
		for (int i = int(rect.top/16); i<(rect.top + rect.height)/16; i++)			//height cycle
			for (int j = int(rect.left/16); j<(rect.left + rect.width)/16; j++)		//width cycle
				 if (!(isTeleported))							//telepotation turns collision off
						switch (map.getTileMap(i,j)) {
							case 'P': collisionCheckSolid(i,j,num); break;	//solid blocks
							case 'g': collisionCheckSolid(i,j,num); break;	//solid blocks
							case 'k': collisionCheckSolid(i,j,num); break;	//brick
							case '0': collisionCheckSolid(i,j,num); break;	//solid empty block
							case 'r': collisionCheckSolid(i,j,num); break;	//other brick
							case 't': collisionCheckSolid(i,j,num); break;	//tube
							case 'T': collisionCheckSolid(i,j,num); break;	//other tube
							case 'e': collisionCheckSolid(i,j,num); break;	//empty bonus block
							case 'j': collisionCheckSolid(i,j,num); break;	//column with platform
							case 'i': collisionCheckSolid(i,j,num); break;	//solid column
							case 'L': collisionLadder(i,j,num);	break;	//ladder
							case 'p': collisionCheckPlatform(i,j,num); break;	//platform
							case 'c': collisionCheckSolidBonus(i,j,num); break;	//bonus
							case 'C': ++coins; coinSound.play(); map.setTileMap(i,j,' '); if (coins>=winCondition) isWon=true; break; //coin
							case 'H': teleport(152,12); teleportSound.play(); break;//tp block
							case 'W':	hurt();										//Player takes damage
									if (alive()) {
										isTeleported=true;							//water teleports us to the nearest block
										if (map.getTileMap(i,j-1)=='W') rect.left=float(j*16-16);		//but it can't tp us on another block of water
										else { rect.top=float(i*16-32); rect.left=float(j*16-32); };		//
										isTeleported=false;							//
									}						
									break;
							case 'U': if (!unicornSound.getStatus()) unicornSound.play(); if (!isHealed) heal(1); break;	//magic healing unicorns!
							case 'u': if (!unicornSound.getStatus()) unicornSound.play(); if (!isHealed) heal(1); break;	//
							};

   }

		void Player::hurt(int damage)	{ //if player hurts
			if (!(isBlinking)) {
					isBlinking=true;		//blinking
					hitSound.play();		//sound
					lives -= damage;		//hurting
					if (lives<0) lives=0;		//no overdeath
					heartsChange();			//sprite update
				};
			}

		void Player::heal(int healing) {
				timeTick=healingClock.getElapsedTime().asSeconds();
				if (timeTick>1) {
						lives += healing;	//adding hp
						if (lives>3) lives=3;	//max hp is 3
						heartsChange();		//sprite update
						isHealed=true;		//for healing cooldown
						healingClock.restart();	//
					};
			};

		inline void Player::spriteUpdate() {	//sprite change
			if (dx>0) (dy==0) ? sprite.setTextureRect(sf::IntRect(112+16*int(currentFrame),144,16,16)) :		//running or jumping to the left
								sprite.setTextureRect(sf::IntRect(162,144,16,16));		//
			if (dx<0) (dy==0) ? sprite.setTextureRect(sf::IntRect(112+16*int(currentFrame)+16,144,-16,16)) : 	//or right
								sprite.setTextureRect(sf::IntRect(178,144,-16,16));		//
			if (dx==0) (dy==0) ?  sprite.setTextureRect(sf::IntRect(97,144,16,16)) :				//standing or falling
								  sprite.setTextureRect(sf::IntRect(162,144,16,16));		//
		}
		
		inline void Player::collisionCheckSolid (int iCoord,int jCoord, int mode) {
				if (dy>0 && mode==1) { rect.top = float(iCoord*16 -  rect.height); dy=0; isOnGround=true; }	//if we hit the floor from above we are on ground
				if (dy<0 && mode==1) { rect.top = float(iCoord*16 + 16); dy=0; }				//we can't hit solid block from below
				if (dx>0 && mode==0)   rect.left = float(jCoord*16 - rect.width);				//if we hit solid block from the side
				if (dx<0 && mode==0)   rect.left = float(jCoord*16 + 16);					//we won't get through it
			}

		void Player::collisionCheckSolidBonus (int iCoord,int jCoord, int mode) {
				if (dy>0 && mode==1) { rect.top = float(iCoord*16 -  rect.height); dy=0; isOnGround=true; }	//if we hit the floor from above we are on ground
				if (dy<0 && mode==1) { rect.top = float(iCoord*16 + 16); dy=0; bonusSound.play();		//if we hit bonus from bottom it spawns coin
									   map.setTileMap(iCoord,jCoord,'e'); map.setTileMap(iCoord-1,jCoord,'C'); }	//
				if (dx>0 && mode==0)   rect.left = float(jCoord*16 - rect.width);							//if we hit solid block from the side
				if (dx<0 && mode==0)   rect.left = float(jCoord*16 + 16);								//we won't get through it
			}

		void Player::updateAxisY(float time){
				rect.top += dy * time;						//getting higher or lower
				sprite.setPosition( rect.left - map.getOffsetX(), rect.top );	//moving background and setting its position
			}

		bool Player::onTube() const {
			if (isOnGround)
				for (int i = int(rect.top/16); i<(rect.top+rect.height)/16; i++)		//height cycle
					for (int j = int(rect.left/16); j<(rect.left+rect.width)/16; j++)	//width cycle
						if (map.getTileMap(i+1,j)=='t')							
							for (int i = int(rect.top/16); i<(rect.top+rect.height)/16; i++)		//height cycle
								for (int j = int(rect.left/16); j<(rect.left+rect.width)/16; j++)	//width cycle
									if (map.getTileMap(i+1,j)=='0') return true;			//if blocks under player are 't' and '0'
			return false;
			};

		inline void Player::collisionCheckPlatform(int iCoord,int jCoord, int mode) {
			//if we hit the platform from above we shouldn't fall and platform banishes for a while
			if (dy>0 && mode==1) 
				if (!(isDownThePlatform)) {
					rect.top = float(iCoord*16 -  rect.height);
					dy=0;
					isOnGround=true;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						isDownThePlatform=true;
						platformClock.restart();
					}
				}
			};

		inline void Player::collisionLadder(int iCoord,int jCoord,int mode) {
			isOnLadder=true;	//player is on ladder
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) dy=float(dy+0.0006);	//go down
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) dy=float(dy-0.0006);	//go up
			else dy=0;				//if he presses nothing he stands still
			if (dy>0.1) dy=float(0.1);		//speed limit down
			else if (dy<-0.1) dy=float(-0.1);	//	      up
		};

		bool Player::canJump() const {
			if (isOnGround)
				for (int i = int(rect.top/16); i<(rect.top+rect.height)/16; i++)				//height cycle
					for (int j = int(rect.left/16); j<(rect.left+rect.width)/16; j++)			//width cycle
						if (solidBlocks.find(map.getTileMap(i-1,j)) != solidBlocks.end())		//solid blocks check
							for (int i = int(rect.top/16); i<(rect.top+rect.height)/16; i++)				//height cycle
								for (int j = int(rect.left/16); j<(rect.left+rect.width)/16; j++)			//width cycle
									if (solidBlocks.find(map.getTileMap(i-1,j)) != solidBlocks.end()) return false;	//if any of blocks just above player are solid
			return true;
			};

		void Player::death() {
				setDeathSprite();				//funny sprite
				setColorSprite(sf::Color::White);		//mario is not blinking and dead
				setDx(0);					//in case of death we have to stop moving in any direction
				setDy(0);					//so offsets are 0
				deathSound.play();				//
			};

		void Player::teleport(int xPos, int yPos) { isTeleported=true; rect = sf::FloatRect(float(xPos*16),float(yPos*16),16,16); };
