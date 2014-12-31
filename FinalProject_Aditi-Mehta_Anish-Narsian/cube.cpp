#include "Cube.h"
#include "Matrix4.h"
#include "Vector3.h"

using namespace std;

Cube::Cube()
{
  angle = 0.0;
  dirx = 1;
  diry = 1;
  countx = 1;
  county = 1;
}

Matrix4& Cube::getMatrix()
{
  return model2world;
}

void Cube::spin(double deg)   // deg is in degrees
{
  angle = deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  Matrix4 tmp;
  tmp.makeRotateY(angle);   // This creates the matrix to rotate the cube
  model2world * tmp;
}

void Cube::translate(double x, double y, double z)
{
	Matrix4 tmp;
	tmp.makeTranslate(x,y,z);
	tmp * model2world;
	model2world = tmp;

}

void Cube::reset()
{
	Matrix4 tmp;
	tmp.identity();
	model2world = tmp;
	model2world.identity();
}

void Cube::scale(double dir)
{
	Matrix4 tmp;
	tmp.makeScale(dir, dir, dir);
	model2world * tmp;
}

void Cube::printPosition() 
{
	Vector3 tmp = model2world.getPos();
	tmp.print("The cube's position is represented by a vector. ");
}

void Cube::rotate(int dir)
{
  Matrix4 tmp;
  Vector3 axis(0,0,1);
  tmp.makeRotate(dir*10, axis);   // This creates the matrix to rotate the cube
  tmp * model2world;
  model2world = tmp;
}

void Cube::bounce()
{
	translate(0.012*dirx, 0.012*diry, 0);
	countx++;
	county++;
	if(countx == 500)
	{
		countx = 1;
		dirx = dirx * (-1);
	}

	if(county == 1000)
	{
		county = 1;
		diry = diry * (-1);
		dirx = dirx * (-1); 
	}
		
}

void Cube::spinx(double deg)   // deg is in degrees
{
  angle = deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  Matrix4 tmp;
  tmp.makeRotateX(angle);   // This creates the matrix to rotate the cube
  model2world * tmp;
}

void Cube::moveToCenter(Vector3 center)
{
	Matrix4 tmp;
	tmp.makeTranslate(center.x,center.y, center.z);
	tmp.print("Translation matrix is: ");
	tmp * model2world;
	model2world = tmp;
}

void Cube::makeWindowSize(int windowWidth, double xdiff)
{
	double dir = (20*tan(30.0/180.0 * M_PI)*2)/(xdiff);
	Matrix4 tmp;
	tmp.makeScale(dir*0.8, dir*0.8, dir*0.8);
	tmp.print("Scaling matrix: ");
	model2world * tmp;
}
