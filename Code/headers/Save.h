#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>	//to interact with sf::Text

class Save {
	std::ostringstream level, coinss, time, date;						// #include <sstream>
	sf::Text levelText, coinsText, timeText, dateText;					//our text
	int numOfLevel, maxCoins, coins, mins, hours, day, month, year;		//our variables
	sf::RenderWindow &window;											//our window
	sf::Font font;														//font of texts
	bool isEmpty;														//is save file empty?
public:
	Save(sf::RenderWindow &_window, int numberOfSave);

	~Save();

	void setAll(int _numOfLevel, int _maxCoins, int _coins, int _mins, int _hours, int _day, int _month, int _year);

	void draw();

	void setIsEmpty(bool _isEmpty) { isEmpty=_isEmpty; }	//setters
	bool getIsEmpty() const { return isEmpty; }				//getters
	};