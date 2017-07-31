#pragma once

#include "LevelMap.h"			//our level
#include "Mushroom.h"			//our mushroom
#include "StartMenu.h"			//our menu

class Level1Map : public LevelMap {

	Entity *mushroom;		//our level 1 enemy
	
	sf::SoundBuffer *smashBuffer;	//smash sound
	sf::Sound *smashSound;		//
	sf::SoundBuffer *pipeBuffer;	//pipe sound
	sf::Sound *pipeSound;		//
	StartMenu *Menu;		//starting menu
	sf::Clock *clockForDown;	//clock for going deeper
	bool *goDeep;			//bool for going deeper
public:
	Level1Map(sf::RenderWindow &window, bool showMenu);

	Level1Map(const Level1Map &_level1map);

	~Level1Map();

	void drawAll() override;

	void drawTiles() override;

	int update() override;

	void reloadLevel() override;

	void pauseEvent() override;

	bool isEnemiesAlive() const override;

	void killEnemies() override;
	};