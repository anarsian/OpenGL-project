#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Matrix4.h"

class Camera
{
  protected:
    Matrix4 c;           // camera matrix
	Vector3 e; 
	Vector3 d;
	Vector3 up;

  public:
	   
    Camera(Vector3&, Vector3&, Vector3&, Matrix4&);   // Constructor
    Matrix4& getMatrix();
	void print();

};

#endif