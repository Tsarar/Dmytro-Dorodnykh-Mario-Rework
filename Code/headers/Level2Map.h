#pragma once

#include "LevelMap.h"		//base level
#include "Slime.h"		//slimes

class Level2Map : public LevelMap {
	
	Entity *slime1,*slime2,*slime3;	//level 2 enemies
	
	sf::SoundBuffer *smashBuffer;	//smash sound (it plays when we kill enemy)
	sf::Sound *smashSound;		//
public:
	Level2Map(sf::RenderWindow &window);
	
	Level2Map(const Level2Map &_level2map);
	
	~Level2Map();
	
	void drawAll() override;
	
	void drawTiles() override;
	
	int update() override;
	
	void reloadLevel() override;

	void pauseEvent();

	void enemyCollision(Entity &slime);

	bool isEnemiesAlive() const override;

	void killEnemies() override;
	};
