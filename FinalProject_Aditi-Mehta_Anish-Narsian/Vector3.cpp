#include <math.h>

#include "Vector3.h"

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator+(const Vector3& a)  //overload operator '+' for addition
{
	return *(new Vector3(this->x + a.x, this->y + a.y, this->z + a.z));
}

Vector3 Vector3::operator-(const Vector3& a)  //overload operator '-' for subtraction
{
	return *(new Vector3(this->x - a.x, this->y - a.y, this->z - a.z));
}

void Vector3::negate() //negation
{
	x = -x;
	y = -y;
	z = -z;
}

void Vector3::scale(double s)  //scale (multiplication with scalar value)
{
	x = s * x;
	y = s * y;
	z = s * z;
}

double Vector3::dot(const Vector3& a, const Vector3& b)  //dot product, returns result
{
	return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
}

void Vector3::cross(const Vector3& a, const Vector3& b)  //cross product, returns result in a new vector
{
   double xcross = a.y*b.z - a.z*b.y;
   double ycross = a.z*b.x - a.x*b.z; 
   double zcross = a.x*b.y - a.y*b.x;
   Vector3 tmp(xcross, ycross, zcross);
   *this = tmp;
}

double Vector3::length()  //length of the vector
{
	return sqrt(x*x+y*y+z*z);
}

void Vector3::normalize()  //normalize the vector (make it so that its length is equal to one)
{
	if(length() != 0) scale(1/length());	
}

void Vector3::print(string comment)  //print x,y and z components of the vector after a comment string 
{
	printf(comment.c_str());
	printf("The components of the vector are as follows: \n");
	printf("x: %.3f \ny: %.3f \nz: %.3f\n\n\n", x, y, z);
}
