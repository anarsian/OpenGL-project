#include "Bezier.h"


Bezier::Bezier(void)
{
}

Bezier::~Bezier(void)
{
}

double Bezier::coeff(double n, double i, double t)
{
	//long n: is the degree of our curve, in the case of a cubic curve it is 3
	//long i: the index of the Bernstein coefficient and the control point
	//double t: is the time we are evaluating at
	

	//Calculate the Bernstein coefficient
	return combo(n, i) * pow(1.0-t, n-i) * pow(t, i);
}

double Bezier::combo(double n, double i)
{
	//C(n, i) = n! / ((n-1)! * i!)
	return factorial(n) / ( factorial(n-i) * factorial(i) );
}

double Bezier::factorial(double n)
{
	double result = 1;

	//If n is 0, by definition 0! is equal to 1
	if(n <= 0)
		return result;

	//Calculate the factorial, n * n-1 * n-2 * ... * 1
	for(double i = n; i > 0; --i)
	{
		result *= i;
	}

	return result;
}

Vector4 Bezier::calculate(double t, Matrix4 mp)
{
	Vector4 C (coeff(3, 0, t),
		coeff(3, 1, t),
		coeff(3, 2, t),
		coeff(3, 3, t));
	//Calculate the final point q
	mp * C;

	//And make sure q is a point by setting its w-component to 1
	C.w = 1.0;
	return C;
}

void Bezier::createPatchStuff()
{
	Matrix4 u0(points[0], points[1], points[2], points[3]);
	Matrix4 u1(points[4], points[5], points[6], points[7]);
	Matrix4 u2(points[8], points[9], points[10], points[11]);
	Matrix4 u3(points[12], points[13], points[14], points[15]);
	double t1 = 0.0, t2 = 0.0;

	for(int i = 0; i <100; i++)
	{
		Vector4 q0 = calculate(t1, u0);
		Vector4 q1 = calculate(t1, u1);
		Vector4 q2 = calculate(t1, u2);
		Vector4 q3 = calculate(t1, u3);
		Matrix4 q(q0, q1, q2, q3);

		Vector4 r0 = calculate(t1 + 0.00001, u0);
		Vector4 r1 = calculate(t1 + 0.00001, u1);
		Vector4 r2 = calculate(t1 + 0.00001, u2);
		Vector4 r3 = calculate(t1 + 0.00001, u3);
		Matrix4 r(r0, r1, r2, r3);
		t2 = 0.0;
		for(int j = 0; j < 100; j++)
		{
			Vector4 tan_u = calculate(t2 + 0.00001, q) - calculate(t2, q);
			Vector4 tan_v = calculate(t2, r) - calculate(t2, q);

			//NORMALIZE
			tan_u.normalize();
			tan_v.normalize();
			
			//CROSS PRODUCT FOR NORMAL
			normals[i][j].cross(tan_u, tan_v);

			//Create vertex!!
			vertices[i][j] = calculate(t2, q);
			t2 = t2 + 0.01;
		}

		t1 +=0.01;
	}
}