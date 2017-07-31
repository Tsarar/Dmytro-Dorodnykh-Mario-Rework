#pragma once

#include "Entity.h"	//slime is a child class of Entity

class Slime : public Entity {
public:
		Slime(LevelMap &_map, sf::Texture &image, int xPos, int yPos);

		~Slime();

		void update(float time) override;	//main procedure

		void collision(int num) override;	//blocks interaction
};