#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "RawDatabase.h"

using namespace std;

string line;
ifstream inFile;

vector<string> stringTokenizer(string str)
{
	stringstream ss(str);
	string temp;
	vector<string> result;

	while(ss>>temp)
	{
		result.push_back(temp);
	}

	return result;
}
void RawDatabase::parseHierarchy(int parent)
{
	string name;
	jhm::vector offset;
	vector<string> dof;
	vector<string> tokens;
	BodyJoint* p = skeleton->findJoint(parent);

	while(1)
	{
			if(line.find("End Site") != string::npos) 
			{
				name = "End Site_" + parent;
				while(line.find("{") == string::npos) getline(inFile, line);
				while(line.find("OFFSET") == string::npos) getline(inFile, line);
				tokens = stringTokenizer(line);
				offset << stof(tokens.at(1)), stof(tokens.at(2)), stof(tokens.at(3));
				BodyJoint* joint = new BodyJoint(name, offset, p);
				p->setChildren(joint);
				bs->addJoint(joint);
			}
			else if(line.find("ROOT") != string::npos || line.find("JOINT") != string::npos)
			{
				name = stringTokenizer(line).at(1);
				while(line.find("{") == string::npos) getline(inFile, line);
				while(line.find("OFFSET") == string::npos) getline(inFile, line);
				tokens = stringTokenizer(line);
				offset << stof(tokens.at(1)), stof(tokens.at(2)), stof(tokens.at(3));
				while(line.find("CHANNELS") == string::npos) getline(inFile, line);
				tokens = stringTokenizer(line);
				for(int i = 0; i < stoi(tokens.at(1)); i++)
				{
					dof.push_back(tokens.at(i+2));
				}
				BodyJoint* joint = new BodyJoint(name, offset, dof, p);
				if(p) p->setChildren(joint);
				else bs->setRoot(joint);
				bs->addJoint(joint);
			}
			
			getline(inFile, line);
			if(line.find("}") != string::npos) 
			{
				break;
			}
			if(line.find("JOINT") != string::npos || line.find("End Site") != string::npos)
			{
				line=parseBVHHierarchy(name, line);
			}
	}
}
void RawDatabase::parseMotion()
{

}
void RawDatabase::parseBVH(char* filename, Type type)
{
	string line;
	inFile.open(filename);

	while(!inFile.eof())
	{
		getline(inFile, line);
		if(type == HIERARCHY && line.find("HIERARCHY") != string::npos)
		{
			skeleton = new PmHuman();
			parseHierarchy(-1);
			break;
		} 
		if(type == MOTION && line.find("MOTION") != string::npos)
		{
			parseMotion();
			break;
		}
	}
	inFile.close();
}
