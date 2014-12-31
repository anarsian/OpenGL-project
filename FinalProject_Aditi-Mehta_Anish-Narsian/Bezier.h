#ifndef _BEZIER_H_
#define _BEZIER_H_

#include "Vector4.h"
#include "Matrix4.h"

class Bezier
{
public:
	Bezier();
	~Bezier(void);
	Vector4 points[16];
	Vector4 normals[100][100];
	Vector4 vertices[100][100];
	double coeff(double n, double i, double t);
	double combo(double n, double i);
	double factorial(double n);
	void createPatchStuff();
	Vector4 calculate(double t, Matrix4 mp);
};

#endif