#include <iostream>
#include <vector>
#include <fstream>
#include "mathclass.h"
#include "pm.h"
#include "RawDatabase.h"

int main()
{
	RawDatabase* database = new RawDatabase();
	database->setCharacter("../data/16");
	database->loadLinearMotions("../data");
	return 0;
}
