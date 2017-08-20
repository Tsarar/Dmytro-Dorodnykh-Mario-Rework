#include "../headers/Errors.h"

Error::Error() {
	codeOfError = -1;				//default code
	description = "Unknown error";
};

Error1::Error1() {
	codeOfError = 1;
	description = "Level not found!";
};

Error2::Error2() {
	codeOfError = 2;
	description = "To be continued...";
};

Error3::Error3() {
	codeOfError = 3;
	description = "Can't find or open save file!";
};