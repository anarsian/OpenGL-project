#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "main.h"
#include "Node.h"

//#include <GL\glut.h>

class robot
{
protected: 
	double angle;

public:
	robot(void);
	~robot(void);

	void drawRobot(double deg, int, int, int, Matrix4, int);

};

#endif