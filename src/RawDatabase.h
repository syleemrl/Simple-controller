#ifndef __RAWDATABASE_H
#define __RAWDATABASE_H
#include <vector>
#include "pm.h"

using namespace std;

class RawDatabase
{
private:
	PmHuman* character;
	vector<PmLinearMotion*> raw;	
	vector<PmLinearMotion*> modified;	
public:
	void setCharacter(PmHuman* ch) { character = ch; };
	PmHuman* getCharacter() { return character; };
	void setCharacter(string str);
	void loadLinearMotions(string str);
	PmLinearMotion* getRawLinearMotion(int i) { return raw.at(i); };
};

#endif
