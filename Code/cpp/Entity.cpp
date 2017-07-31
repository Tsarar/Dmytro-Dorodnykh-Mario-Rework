#include "../headers/Entity.h"

	Entity::Entity(LevelMap &_map) : map(_map){
		dx = new float;				//heap usage
		dy = new float;				//
		rect = new sf::FloatRect;	//
		sprite = new sf::Sprite;	//
		currentFrame = new float;	//
		life = new bool;			//

		*life = true;				//default alive
	};
	
	Entity::~Entity() {
		delete life;		//freeing memory
		delete currentFrame;//
		delete sprite;		//
		delete rect;		//
		delete dy;			//
		delete dx;			//
	}
	
	inline void Entity::teleport(int xPos, int yPos)  {						//placing our entity
				*rect = sf::FloatRect(float(xPos*16),float(yPos*16),16,16);	//at that position
			}