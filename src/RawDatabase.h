#ifndef __RAWDATABASE_H
#define __RAWDATABASE_H
#include <vector>
#include <pm.h>

using namespace std;

enum Type {HIERARCHY, MOTION};

class RawDatabase
{
private:
	PmHuman* skeleton;
	std::vector<PmLinearMotion*> lm;	
	void parseHierarchy(int parent);
	void parseMotion();
public:
	void parseBVH(char* fileName, Type type);
};

#endif
