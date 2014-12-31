#include <string>

#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#define M_PI 3.14159265358979323846

using namespace std;

class Vector4
{
    public:

	double x;   
	double y;
	double z;
	double w;
	Vector4();
	Vector4(double x, double y, double z, double w); //constructor with four parameters for the vector coordinates
	Vector4 operator+(const Vector4&); //overload operator '+' for addition
	Vector4 operator-(const Vector4&); //overload operator '-' for subtraction
	void dehomogenize(); //dehomogenize the vector (scale it so that its fourth component is equal to one)
	void print(string comment); //print x,y, z and w components of the vector after a comment string 
	double dot(const Vector4&); //dot product, returns result
	void cross(const Vector4&, const Vector4&);
	void normalize();
};

#endif