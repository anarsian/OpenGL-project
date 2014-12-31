#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"

class Cube
{
  protected:
    Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
    double angle;                   // rotation angle [degrees]
	int dirx;
	int diry;
	int countx, county;

  public:
    Cube();   // Constructor
    Matrix4& getMatrix();
    void spin(double);      // spin cube [degrees]
	void translate(double x, double y, double z); //move cube
	void reset(); 
	void scale(double); //scale up or down 
	void printPosition();   //print position of the cube
	void rotate(int);    //rotate cube about z axis of screen
	void bounce(); //bounce ball
	void spinx(double);
	void moveToCenter(Vector3);
	void makeWindowSize(int, double);
};

#endif

