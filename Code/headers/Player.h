#pragma once

#include "LevelMap.h"	//for map

//player is a special entity, that is included in every level, so if it would be inherited form Entity class
//it would cause some logical troubles. That's why it copies all Entity class functions without beeing inherited
//despite it can be very convenient

class Player {							//player
		float dx,dy;					//offset (this is needed for movement)
		sf::FloatRect rect;				//void zone
		sf::Sprite sprite;				//image
		float currentFrame;				//frame
		bool isOnGround;				//onground check
		bool isTeleported;				//teleported check
		bool isBlinking;				//blinking check
		int damageTicks;				//counter for color of blinking
		sf::Clock damageClock;			//clocks for blinking
		sf::Clock healingClock;			//		 for healing
		sf::Clock platformClock;		//		 for platform
		bool isHealed;					//healing cooldown
		float timeTick;					//counter for blinking and healing
		int lives;						//lives
		sf::Texture livesTexture;		//hearts
		sf::Sprite hearts;				//
		class LevelMap &map;			//our map, program uses mutual recursion structure, so we use forward declaration
		int coins;						//amount of coins
		bool isWon;						//for winning
		sf::SoundBuffer hitBuff,coinBuff,teleportBuff,unicornBuff,bonusBuff,deathBuff;		//sounds and buffers
		sf::Sound hitSound,coinSound,teleportSound,unicornSound,bonusSound,deathSound;		//
		int currentLevel;				//currentLevel
		bool isDownThePlatform;			//are we recently fell off a platform
		int winCondition;				//amount of coins to win
		bool isOnLadder;				//
		std::set<char> solidBlocks;		//set of solid blocks
public:
		Player(LevelMap &_map);

		~Player();

		void update(float time);

		void collision(int num);

		void teleport(int xPos, int yPos);	//teleporting procedure
		
		void hurt(int damage = 1);	//if player takes damage
		void heal(int healing);		//or heals
		void heartsChange() { hearts.setTextureRect( sf::IntRect(0,20*(3-lives),63,19) ); };	//changing texture

		float getDx() const { return dx; }											//getters
		bool getOnGround() const { return isOnGround; }								//
		float getDy() const { return dy; }											//
		inline sf::Sprite getSprite() const { return sprite; }						//
		sf::FloatRect getRect() const { return rect; }								//
		int	getLives() const { return lives;}										//
		sf::Sprite getHearts() const { return hearts;}								//
		bool alive() const { if (lives>0) return true; else return false;}			//
		int getCoins() const { return coins; }										//
		bool playerIsWon() const { return isWon; }									//
		int getCurrentLevel() const { return currentLevel; }						//
		void setDx(double _dx) { dx=float(_dx); }									//setters
		void setDy(double _dy) { dy=float(_dy); }									//
		void setOnGround()  { isOnGround=true; }									//
		void setOnGround(bool _isOnGround)  { isOnGround=_isOnGround; }				//
		void setColorSprite(sf::Color _color) { sprite.setColor(_color); }			//
		void setBlinking(bool _isBlinking) { isBlinking = _isBlinking; }			//
		void setLives(int _lives)	{ lives = _lives; }								//
		void setTeleported() { isTeleported = true; }								//
		void setTeleported(bool _isTeleported) { isTeleported = _isTeleported; }	//
		void addCoin() { coins = coins + 1; }										//
		void setCoins(int _coins) { coins=_coins; }									//
		void setIsWon() { isWon=true; }												//
		void setIsWon(bool _isWon) { isWon=_isWon; }								//	
		void setCurrentLevel(int _currLevel) { currentLevel=_currLevel; }			//
		void setWinCondition(int _winCondition) { winCondition=_winCondition; }		//

		void setSprite(sf::Texture &_image) {
			sprite.setTexture(_image);				//our texture
			rect = sf::FloatRect(5*16,5*16,16,16);	//rectangle 16x16 plus random position
		};

		inline void spriteUpdate();											//sprite change
		inline void collisionCheckSolid(int iCoord,int jCoord, int mode);	//collision with solid blocks
		void collisionCheckSolidBonus(int iCoord,int jCoord, int mode);		//with bonus block
		void collisionCheckPlatform(int iCoord,int jCoord, int mode);		//with platform
		void collisionLadder(int iCoord,int jCoord, int mode);				//with ladder

		void setDeathSprite() { sprite.setTextureRect(sf::IntRect(184,144,16,16)); }	//for death
		void updateAxisY(float time);													//update only y axis, light update function
		bool onTube() const;															//checking if mario on tube
		bool canJump() const;															//		   if mario can jump
		void death();																	//preaparing  for death
};