#ifndef __RAWDATABASE_H
#define __RAWDATABASE_H
#include <vector>
#include "pm.h"

using namespace std;

class RawDatabase
{
private:
	PmHuman* character;
	PmLinearMotion* base;
	vector<PmLinearMotion*> raw;	
	vector<PmLinearMotion*> modified;	
public:
	void setCharacter(PmHuman* ch) { character = ch; };
	PmHuman* getCharacter() { return character; };
	void setCharacter(string str);
	void loadLinearMotions(string str);
	void cropLinearMotions();
	PmLinearMotion* getBaseMotion() { return base; };
	PmLinearMotion* getRawLinearMotion(int i) { return raw.at(i); };
	PmLinearMotion* getModifiedLinearMotion(int i) { return modified.at(i); };
};

#endif
