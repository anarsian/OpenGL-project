#include <string>

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#define M_PI 3.14159265358979323846

using namespace std;

class Vector3
{
public:
	double x;   
	double y;
	double z;

	Vector3();
	Vector3(double x, double y, double z); //constructor with three parameters for the vector coordinates 
	Vector3 operator+(const Vector3&);  //overload operator '+' for addition
    Vector3 operator-(const Vector3&);  //overload operator '-' for subtraction
	void negate(); //negation
	void scale(double s); //scale (multiplication with scalar value)
	double dot(const Vector3&, const Vector3&); //dot product, returns result
	void cross(const Vector3&, const Vector3&); //cross product, returns result 
	double length(); //length of the vector
	void normalize(); //normalize the vector (make it so that its length is equal to one)
	void print(string comment); //print x,y and z components of the vector after a comment string 
};

#endif