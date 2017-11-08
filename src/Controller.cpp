#include <iostream>
#include <vector>
#include <fstream>
#include "mathclass.h"
#include "pm.h"
int main()
{
	PmHuman* character;
	vector<pmLinearMotion*> lms;
	character->ConvertASF2ACTOR("../data/16.asf","../data/16.actor",1.0);
	character = new PmHuman("../data/16.actor");
	return 0;
}
