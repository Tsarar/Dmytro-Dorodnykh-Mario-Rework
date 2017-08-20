#include "../headers/Entity.h"

	Entity::Entity(LevelMap &_map) : map(_map){
		life = true;				//default alive
	};
	
	Entity::~Entity() {}
	
	inline void Entity::teleport(int xPos, int yPos)  {						//placing our entity
				rect = sf::FloatRect(float(xPos*16),float(yPos*16),16,16);	//at that position
			}