#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>	//for map 
#include <sstream>	//for coin and ups messages
#include <fstream>	//for saving in saveTofile() and loadFromFile()
#include <ctime>	//to save current time in saveToFile()
#include "Player.h"	//our player
#include "DeathMenu.h"	//for death
#include "ErrorWindow.h"//for errors
#include "SaveWindow.h"	//for saving system

class LevelMap {	//abstract class of any level
protected:
		static const int H = 17;	//height of the level
		int W;				//weight of the level
		int *numberOfLevel;		//number of level
		float offsetX;			//starting offset
		float offsetY;			//
		std::string TileMap[H];		//field

		sf::Texture tileSet;		//main texture
		sf::Sprite tile;		//block for drawing level
		sf::SoundBuffer *jumpBuff;	//jump sound
		sf::Sound *jump;		//
		sf::Music *music;		//background music
		sf::Clock *clock;		//main clock
		float time;			//delay between updates/time for locking speed
		sf::Clock *clockPause;		//clock for pause
		float *timerPause;		//
		bool *pause;			//pause
		sf::Texture *pauseTexture;	//pause message
		sf::Sprite *pauseSprite;	//
		sf::Sprite *winSprite;		//win message
		sf::Texture *winTexture;	//
		DeathMenu *DMenu;		//death menu
		sf::Font font;			//font for texts
		sf::Sprite *coin;		//coin texture
		sf::Text coinText;		//coins counter
		std::ostringstream coins;	// #include <sstream>
		std::ostringstream ups;		// #include <sstream> ups message
		sf::Clock upsClock;		//ups settings
		sf::Text upsText;			//
		bool *showUps;				//
		int counter;				//ups counter
		int rightConst;				//to avoid math in cycle
		int *coinsToWin;			//amount of coins to win the level
		sf::Text *saveText;			//"Game has been saved" text
		sf::Clock *saveClock;			//
		float *realOffset;			//offset x for correct load tp
		unsigned char colorX,colorY,colorZ;	//background color, using char type to save space

		sf::RenderWindow &window;		//window
		class Player *Mario;			//our player, program uses mutual recursion structure, so we use forward declaration

		LevelMap::LevelMap(sf::RenderWindow &_window);
		
		virtual void drawTiles() = 0;	//drawing map (tiles sprites)

		virtual void drawAll() = 0;	//drawing all exept map (sprites)

		virtual void reloadLevel() = 0;	//reloading all properties of level

		virtual void basicControls();

		virtual int eventHandling();
		
		virtual void pauseEvent();

		virtual void changeOffsets();

		virtual void playerDeath(float time);

		virtual bool isEnemiesAlive() const = 0;

		virtual void killEnemies() = 0;
public:
	
		virtual int update() = 0;

		virtual ~LevelMap();

		virtual void LevelMap::reloadMap();	//reloading any map with coins

		virtual void loadFromFile(int numOfSave);
		virtual void saveToFile(int numOfSave) const;

		inline void setOffsetX(float _offsetX) { offsetX=_offsetX; }				//setters
		inline void setOffsetY(float _offsetY) { offsetY=_offsetY; }				//
		void setW(int bufW) { W=bufW; }												//
		void setTileMap(int x,int y,char block) { TileMap[x][y]=block; }			//
		void setNumOfLevel(int _numberOfLevel) { *numberOfLevel=_numberOfLevel; }	//
		void setMaxCoins(int _maxCoins) { *coinsToWin=_maxCoins; }					//
		inline float getOffsetX() const { return offsetX; }							//getters
		inline float getOffsetY() const { return offsetY; }							//
		inline char getTileMap(int x,int y) const { return TileMap[x][y]; }			//
		inline int getH() const { return H; }										//
		inline int getW() const { return W; }										//
		int getNumberOfLevel() const { return *numberOfLevel; }						//
		int getMaxCoins() const { return *coinsToWin; }								//
		float getRealOffset() const { return *realOffset; }							//
	};