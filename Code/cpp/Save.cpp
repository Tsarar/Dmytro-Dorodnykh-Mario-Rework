#include "../headers/Save.h"

	Save::Save(sf::RenderWindow &_window, int numberOfSave) : window(_window) {
		level = new std::ostringstream;		//getting memory from heap
		coinss = new std::ostringstream;	//
		time = new std::ostringstream;		//
		date = new std::ostringstream;		//
		levelText = new sf::Text;		//
		coinsText = new sf::Text;		//
		timeText = new sf::Text;		//
		dateText = new sf::Text;		//
		isEmpty = new bool;			//

		font.loadFromFile("fonts/sansation.ttf");	//font loading

		levelText->setString("");					//placing level text
		levelText->setCharacterSize(14);				//
		levelText->setFont(font);					//
		levelText->setColor(sf::Color::White);				//
		levelText->setPosition(70,float(25+70*(numberOfSave-1)));	//

		coinsText->setString("");					//placing coins text
		coinsText->setCharacterSize(14);				//
		coinsText->setFont(font);					//
		coinsText->setColor(sf::Color::White);				//
		coinsText->setPosition(70,float(45+70*(numberOfSave-1)));	//

		timeText->setString("");					//placing time text
		timeText->setCharacterSize(14);					//
		timeText->setFont(font);					//
		timeText->setColor(sf::Color::White);				//
		timeText->setPosition(270,float(25+70*(numberOfSave-1)));	//

		dateText->setString("");					//placing date text
		dateText->setCharacterSize(14);					//
		dateText->setFont(font);					//
		dateText->setColor(sf::Color::White);				//
		dateText->setPosition(270,float(45+70*(numberOfSave-1)));	//

		*isEmpty=true;
	};

	Save::~Save() {
		delete level;		//freeing memory
		delete coinss;		//
		delete time;		//
		delete date;		//
		delete levelText;	//
		delete coinsText;	//
		delete timeText;	//
		delete dateText;	//
		delete isEmpty;		//
	};

	void Save::draw(){
		level->str("");						//setting text
		coinss->str("");					//
		time->str("");						//
		date->str("");						//
		if (getIsEmpty()) levelText->setString("Empty");	//if file is empty
		else {
				*level << "Level: " << numOfLevel;		//setting number of level
				levelText->setString( level->str() );		//
				*coinss << "Coins: " << coins << '/' << maxCoins;//setting coins
				coinsText->setString( coinss->str() );		//
				if (hours<10) *time << '0';			//setting time
				*time << hours << ':';				//
				if (mins<10) *time << '0';			//
				*time << mins;					//
				timeText->setString( time->str() );		//
				if (day<10) *date << '0';			//setting date
				*date << day << '.';				//
				if (month<10) *date << '0';			//
				*date << month << '.' << year;			//
				dateText->setString( date->str() ); 		//
				window.draw(*coinsText);			//
				window.draw(*timeText);				//
				window.draw(*dateText);				//
			}
		window.draw(*levelText);					//drawing everything

	};

	void Save::setAll(int _numOfLevel, int _maxCoins, int _coins, int _mins, int _hours, int _day, int _month, int _year) {
		numOfLevel=_numOfLevel;	//setting information about save
		maxCoins=_maxCoins;	//
		coins=_coins;		//
		mins=_mins;		//
		hours=_hours;		//
		day=_day;		//
		month=_month;		//
		year=_year;		//
	};
