#pragma once

#include <string>

//my simple class with exceptions

class Error {
protected:
	int codeOfError;
	std::string description;
public:
	Error();
	virtual ~Error() {};

	int getCode() const { return codeOfError; } 
	std::string getDescription() const { return description; }
};

class Error1 : public Error {
public:
	Error1();
	~Error1() {};
};

class Error2 : public Error {
public:
	Error2();
	~Error2() {};
};
class Error3 : public Error {
public:
	Error3();
	~Error3() {};
};