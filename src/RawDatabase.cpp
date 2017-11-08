#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <boost/filesystem.hpp>
#include "RawDatabase.h"

using namespace boost::filesystem;
using namespace std;

void RawDatabase::setCharacter(string str)
{
	char *asf = new char[str.length() + 5];
	char *actor = new char[str.length() + 7];
	std::strcpy(asf, (str + ".asf").c_str());
	std::strcpy(actor, (str + ".actor").c_str());
	character->ConvertASF2ACTOR(asf,actor,1.0);
	character = new PmHuman(actor);
}
void RawDatabase::loadLinearMotions(string str)
{
	vector<string> files;
	path p(str);

	directory_iterator end_itr;

	for(directory_iterator iter(p); iter != end_itr; iter++)
	{
		string current_file = iter->path().string();
		if(current_file.find(".amc") != string::npos) files.push_back(current_file);
	}

	PmLinearMotion* tempLM;

	for(int i = 0; i < files.size(); i++)
	{
		tempLM = new PmLinearMotion(character);
		char *amc = new char[files.at(i).length() + 5];
		std::strcpy(amc, files.at(i).c_str());
		tempLM->openAMC(amc);
		tempLM->setFootConstraints(0.4, 2.2, 0.4, 4.5);
		raw.push_back(tempLM);
	}
}
void RawDatabase::cropLinearMotions()
{
	for(int i = 0; i < raw.size(); i++)
	{
		PmLinearMotion* rawLM = raw.at(i);
		int start = rawLM->getSize();
		int end = 0;
		for(int j = 0; j < rawLM->getSize(); j++)
		{
			if(rawLM->isRightToeOff(j)) 
			{
				if(j < start) start = j;
				if(j > end) end = j;
			}
		}
		PmLinearMotion* modifiedLM = new PmLinearMotion(character);
		modifiedLM->crop(*rawLM, start, end - start + 1);
		modified.push_back(modifiedLM);
	}
}
