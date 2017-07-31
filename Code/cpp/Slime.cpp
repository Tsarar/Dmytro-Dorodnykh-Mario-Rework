#include "../headers/Slime.h"

	Slime::Slime(LevelMap &_map, sf::Texture &image, int xPos, int yPos) : Entity(_map)  {
			sprite->setTexture(image);	//texture load
			teleport(xPos,yPos);		//his rect plus starting position
	
			*dx=float(0.07);			//speed
			*currentFrame = 0;			//first frame
		};
	
	Slime::~Slime() {};
	
	void Slime::update(float time) {
			if (*life) {	//interactions only when he is alive, but sprite drawing is needed even when slime dies
				rect->left += *dx * time;		//unbounding him
	
				collision(0);					//blocks interaction

				*currentFrame = *currentFrame + time * float(0.005);	//frame change
				if (*currentFrame > 3) *currentFrame = 0;				//cycling
			};

			if (*life) { (*dx>0) ? sprite->setTextureRect(sf::IntRect(16*int(*currentFrame),32,16,16)) : sprite->setTextureRect(sf::IntRect(16*int(*currentFrame)+16,32,-16,16)); }	//animation
			else sprite->setTextureRect(sf::IntRect(48,32,16,16));																													//

			sprite->setPosition(rect->left - map.getOffsetX(), rect->top);	//moving sprite,  y coord doesn't matter

		};

	void Slime::collision(int num) {
		for (int y = int(rect->top/16); y<(rect->top+rect->height)/16; y++)				//height
			for (int x = int(rect->left/16); x<(rect->left+rect->width)/16; x++)		//width
				 if ((map.getTileMap(y,x)=='k') || (map.getTileMap(y,x)=='i') || (map.getTileMap(y,x)=='t'))	//solid block
					{ if (*dx>0)	{ rect->left = x*16 - rect->width; *dx=*dx*(-1); }			//changing direction to opposite
						else if (*dx<0)	{ rect->left = float(x*16) + 16; *dx=float(*dx*(-1)); }	//										
					 }
		};