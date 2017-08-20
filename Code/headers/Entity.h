#pragma once

#include "LevelMap.h"		//for map

class Entity {				//abstract class of any enemy creature
protected:
	float dx, dy;			//offset (this is needed for movement)
	sf::FloatRect rect;		//void zone
	sf::Sprite sprite;		//image
	float currentFrame;		//frame
	class LevelMap &map;		//our level map
	bool life;			//is creature alive?
public:

	Entity(LevelMap &_map);

	virtual ~Entity();

	virtual void teleport(int xPos, int yPos);

	virtual void update(float time) = 0;	//main procedure

	virtual void collision(int num) = 0;	//blocks interaction, num in case of two-dimensional entity

	bool getLife() const { return life; }					//getters
	sf::FloatRect getRect()	const { return rect; }				//
	inline sf::Sprite getSprite() const { return sprite; }			//
	void setLife(bool _life) { life=_life; }				//setters
	void setDx(double _dx)	 { dx=float(_dx); }				//

	};
