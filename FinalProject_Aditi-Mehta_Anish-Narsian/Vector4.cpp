#include <math.h>

#include "Vector4.h"

Vector4::Vector4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}
Vector4::Vector4(double x, double y, double z, double w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4 Vector4::operator+(const Vector4& a) //overload operator '+' for addition
{
	return *(new Vector4(this->x + a.x, this->y + a.y, this->z + a.z, this->w + a.w));
}

Vector4 Vector4::operator-(const Vector4& a) //overload operator '-' for subtraction
{
	return *(new Vector4(this->x - a.x, this->y - a.y, this->z - a.z, this->w - a.w));
}

void Vector4::dehomogenize() //dehomogenize the vector (scale it so that its fourth component is equal to one)
{
	if (w == 0) return;
	x = x/w;  
	y = y/w;
	z = z/w;
	w = 1;
}

void Vector4::print(string comment) //print x,y, z and w components of the vector after a comment string 
{
	printf(comment.c_str());

	printf("The components of the vector are as follows: \n");
	printf("x: %.3f \ny: %.3f \nz: %.3f \nw: %.3f", x, y, z, w);
}

double Vector4::dot(const Vector4& a)  //dot product, returns result
{
	return (a.x*this->x)+(a.y*this->y)+(a.z*this->z)+(a.w*this->w);
}

void Vector4::normalize()
{
	double s = sqrt(x*x+y*y+z*z);
	if(s != 0)
	{
		s = 1.0/s;
		x = s * x;
		y = s * y;
		z = s * z;
	}

}

void Vector4::cross(const Vector4& a, const Vector4& b)
{
	this->x = a.y*b.z - a.z*b.y;
	this->y = a.z*b.x - a.x*b.z; 
	this->z = a.x*b.y - a.y*b.x;

}