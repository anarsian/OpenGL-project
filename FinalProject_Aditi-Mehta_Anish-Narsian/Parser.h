#ifndef _PARSER_H_
#define _PARSER_H_

#include "Vector3.h"
#include <vector>

class Parser
{
protected:
	double maxx, maxy, maxz, minx, miny, minz;
public:
	vector<int> indices;
	vector<Vector3> normals;
	vector<Vector3> vertices;
	Parser(char* filename, int);
	Parser();
	void parse(char* filename);
	void parse2(char* filename);
	void findMaxMin();

	Vector3 findCenter();

	double findScaleFactor();
};


#endif 
