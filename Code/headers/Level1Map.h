#pragma once

#include "LevelMap.h"			//base level
#include "Mushroom.h"			//mushroom
#include "StartMenu.h"			//menu

class Level1Map : public LevelMap {

	Entity *mushroom;		//level 1 enemy
	
	sf::SoundBuffer *smashBuffer;	//smash sound
	sf::Sound *smashSound;		//
	sf::SoundBuffer *pipeBuffer;	//pipe sound
	sf::Sound *pipeSound;		//
	StartMenu *Menu;		//starting menu
	sf::Clock *clockForDown;	//clock for going deeper
	bool goDeep;			//bool for going deeper
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
