#include "../headers/Mushroom.h"

	Mushroom::Mushroom(LevelMap &_map, sf::Texture &image, int xPos, int yPos) : Entity(_map) {
				sprite.setTexture(image);	//texture load
				teleport(xPos,yPos);		//his rect plus starting position

				dx=float(0.05);				//speed
				currentFrame = 0;			//first frame
			};

	Mushroom::~Mushroom() {};

	void Mushroom::update(float time)	{	
			//interactions only when he is alive, but sprite drawing is needed even when mush dies
			if (life) {						
					rect.left += dx * time;	//unbounding him
	
					collision(0);			//blocks interaction

					currentFrame += time * float(0.005);	//frame change
					if (currentFrame > 2) currentFrame = 0;	//cycling
				};

			life ? sprite.setTextureRect(sf::IntRect(16*int(currentFrame),0,16,16))	//animation
				 : sprite.setTextureRect(sf::IntRect(32, 0, 16,16));				//

			sprite.setPosition(rect.left - map.getOffsetX(), rect.top);	//moving sprite,  y coord doesn't matter

		   };
	
	void Mushroom::collision(int num) {
		for (int y = int(rect.top/16); y<(rect.top+rect.height)/16; y++)			//height
			for (int x = int(rect.left/16); x<(rect.left+rect.width)/16; x++)		//width
				 if ((map.getTileMap(y,x)=='P') || (map.getTileMap(y,x)=='0'))		//solid block
					{ if (dx>0)	{ rect.left = x*16 - rect.width; dx *= -1; }			//changing direction to opposite
						else if (dx<0)	{ rect.left = float(x*16) + 16; dx *= -1; }	//										
					 }
		   };