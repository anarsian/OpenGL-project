#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;


Parser::Parser(char* filename, int flag)
{
	minx = INT_MAX;
	maxx = INT_MIN;
	miny = INT_MAX;
	maxy = INT_MIN;
	minz = INT_MAX;
	maxz = INT_MIN;
	normals = *(new vector<Vector3>);
	vertices = *(new vector<Vector3>);
	indices = *(new vector<int>);
	if (flag == 1) parse(filename);
	else parse2(filename);
}
Parser::Parser()
{

}


void Parser::parse(char* filename)
{
	FILE* fp;     // file pointer
	float x,y,z;  // vertex coordinates
	int c1,c2;    // characters read from file
	int a,l,c,d,e,f;
	fp = fopen(filename,"rb");
	if (fp==NULL) { cerr << "error loading file" << endl; exit(-1); }
	while (true)
	{
		if(feof(fp)) break;
		c1 = fgetc(fp);
		c2 = fgetc(fp);
		if (c1=='f' || c2 == 'f')
		{
			if(c2 != ' ') c2 = fgetc(fp);
			a = l = c = d = e = f = 0;
			fscanf(fp, "%d//%d %d//%d %d//%d", &a, &l, &c, &d, &e, &f);
			indices.push_back(a);
			indices.push_back(l);
			indices.push_back(c);
			indices.push_back(d);
			indices.push_back(e);
			indices.push_back(f);
		}
		if ((c1=='v') && (c2=='n'))
		{
			//c = fgetc(fp);
			fscanf(fp, "%f %f %f", &x, &y, &z);
			Vector3 *normal = new Vector3(x,y,z);
			normal->normalize();
			normals.push_back(*normal);
		}

		if ((c1=='v') && (c2==' '))
		{
			fscanf(fp, "%f %f %f", &x, &y, &z);
			Vector3 *vertex = new Vector3(x,y,z);
			vertices.push_back(*vertex);
		}
	}
	fclose(fp);   // make sure you don't forget to close the file when done
}

void Parser::parse2(char* filename)
{
	FILE* fp;     // file pointer
	float x,y,z;  // vertex coordinates
	float r,g,b;  // vertex color
	int c1,c2;    // characters read from file
	int a,l,c,d,e,f;
	fp = fopen(filename,"rb");
	if (fp==NULL) { cerr << "error loading file" << endl; exit(-1); }
	while (true)
	{
		if(feof(fp)) break;
		c1 = fgetc(fp);
		c2 = fgetc(fp);
		if ((c1=='v') && (c2=='n'))
		{
			fscanf(fp, "%f %f %f", &x, &y, &z);
			Vector3 *normal = new Vector3(x,y,z);
			normal->normalize();
			normals.push_back(*normal);
		}

		else if ((c1=='v') && (c2==' '))
		{
			fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
			Vector3 *vertex = new Vector3(x,y,z);
			vertices.push_back(*vertex);
		}

		else if ((c1=='f') && (c2==' '))
		{
			a = l = c = d= e= f= 0;
			fscanf(fp, "%d//%d %d//%d %d//%d", &a, &l, &c, &d, &e, &f);
			indices.push_back(a);
			indices.push_back(l);
			indices.push_back(c);
			indices.push_back(d);
			indices.push_back(e);
			indices.push_back(f);
		}
	}
	fclose(fp);   // make sure you don't forget to close the file when done
}

void Parser::findMaxMin()
{
	minx = INT_MAX;
	maxx = INT_MIN;
	miny = INT_MAX;
	maxy = INT_MIN;
	minz = INT_MAX;
	maxz = INT_MIN;
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		if(vertices[i].x < minx)
			minx = vertices[i].x;
		if(vertices[i].x > maxx)
			maxx = vertices[i].x;
	}

	for(unsigned int j = 0; j < vertices.size(); j++)
	{
		if(vertices[j].y < miny)
			miny = vertices[j].y;
		if(vertices[j].y > maxy)
			maxy = vertices[j].y;
	}

	for(unsigned int k = 0; k < vertices.size(); k++)
	{
		if(vertices[k].z < minz)
			minz = vertices[k].z;
		if(vertices[k].z > maxz)
			maxz = vertices[k].z;
	}


	printf("The minimum values are: x: %f y: %f z: %f\n", minx, miny, minz);
	printf("The maximum values are: x: %f y: %f z: %f\n", maxx, maxy, maxz);
}

Vector3 Parser::findCenter()
{
	double centerx = (minx + maxx)/2;
	double centery = (miny + maxy)/2;
	double centerz = (minz + maxz)/2;
	Vector3 center =  *(new Vector3(-centerx, -centery, -centerz));
	center.print("Center: ");
	if(centerx == 0 && centery == 0 && centerz == 0)
		return center;
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		vertices[i] = vertices[i] + center;
	}
	return center;

}

double Parser::findScaleFactor()
{
	return maxx - minx;
}

