#include "Camera.h"
#include "Vector3.h"

Camera::Camera(Vector3& up, Vector3& e, Vector3& d, Matrix4& )
{
	this->e = e; 
	this->d = d;
	this->up = up;         
	Vector3 z = (e - d);
	z.normalize();
	Vector3 x;
	x.cross(up, z);
	x.normalize();
	Vector3 y;
	y.cross(z, x);
	y.normalize();

	Vector4 xaxis(x.x, x.y, x.z, 0);
	Vector4 yaxis(y.x, y.y, y.z, 0);
	Vector4 zaxis(z.x, z.y, z.z, 0);
	Vector4 waxis(e.x, e.y, e.z, 1);

	c.m[0][0] = x.x;
	c.m[1][0] = x.y;
	c.m[2][0] = x.z;
	c.m[3][0] = 0;

	c.m[0][1] = y.x;
	c.m[1][1] = y.y;
	c.m[2][1] = y.z;
	c.m[3][1] = 0;

	c.m[0][2] = z.x;
	c.m[1][2] = z.y;
	c.m[2][2] = z.z;
	c.m[3][2] = 0;

	c.m[0][3] = e.x;
	c.m[1][3] = e.y;
	c.m[2][3] = e.z;
	c.m[3][3] = 1;

}


Matrix4& Camera::getMatrix()
{
	return c;
}

void Camera::print()
{
	this->c.print("Camera: ");
}