#pragma once

#include "Entity.h"	//mushroom is a child class of entity


class Mushroom	: public Entity			//our mush
	{
	public:
		Mushroom(LevelMap &_map, sf::Texture &image, int xPos, int yPos);

		~Mushroom();

		void update(float time) override;	//main procedure

		void collision(int num) override;	//blocks interaction
};