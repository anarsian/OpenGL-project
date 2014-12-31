//
//  Turtle.cpp
//  Final Project
//
//  Created by anish Narsian on 12/14/14.
//  Copyright (c) 2014 Anish Narsian. All rights reserved.
//

#include "Turtle.h"

#include <GL/glut.h>
//#include </gl.h>

#include <math.h>
#include "Window.h"
#include <iostream>

float PI = 3.141592654f;

float x=0;
float y=0;
float z = 0;
float theta=0;
bool draw=true;


Turtle::Turtle() {
	currx = 0;
	curry =0;
	currz =0;
	ang = 0;
	M.identity();
	H = Vector4(0.0,0.0,-1.0,0.0);
	L = Vector4(-1.0,0.0,0.0,0.0);
	U = Vector4(0.0,1.0,0.0,0.0);
	wComp = Vector4(0.0,0,0,1.0);//represents origin potentiallly
	tMat = Matrix4(H,L,U,wComp);
}

void Turtle::rotateH(double a) {


}

void Turtle::rotateL(double a) {

}

void Turtle::rotateU(double a) {

}


void Turtle::Init(float _x,float _y,float _z, float _theta)
{
	// Turtle a;
	x = _x;
	currx = x;
	y = _y;
	curry = y;
	z = _z;
	currz = z;
	theta = _theta;
	ang = theta;
}


void Turtle::Forward(float dist)
{
	x = currx;
	y =curry;
	z = currz;

	theta = ang;


	Vector4 tmp = Vector4(x,y,z,0);

	M*tmp;

	float lx = dist*tmp.x;
	float ly = dist*tmp.y;
	float lz = dist*tmp.z;
	//float lz = dist*tmp.v4[2];

	float x1 = x + lx;
	float y1 = y + ly;
	float z1 = z + lz;



	if(y1 > 6.5)
		return;

	if(draw){
		if(y<1) {
			glLineWidth(8);
		}
		else if (y < 2)
			glLineWidth(5);
		else
			glLineWidth(3);

		Vector3 tmp(x,y,z);
		Vector3 tmp2(x1,y1,z1);
		Vector3 n;
		n.cross(tmp, tmp2);

		glBegin(GL_LINE_STRIP);
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(x, y, z);
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(x1, y1, z1);

		glEnd();

	}

	x = x1;
	y = y1;
	z = z1;
	currx = x;
	curry = y;
	currz = z;
	ang = theta;

}



void Turtle::Right(float _theta)
{

	x = currx;
	y =curry;
	z = currz;
	theta = ang;
	theta = theta - _theta;
	if(theta < 0){
		theta = 360 + theta;
	}
	ang = theta;
	Matrix4 temp;
	temp.makeRotateY(theta);
	M * temp;
	M.transpose();
}

void Turtle::Left(float _theta)
{
	x = currx;
	y =curry;
	z = currz;
	theta = ang;
	theta = theta + _theta;
	if(theta > 360){
		theta = theta - 360;
	}

	ang = theta;
	Matrix4 temp;
	temp.makeRotateY(theta);
	M*temp;
	//M.makeRotateZ(theta);
	M.transpose();
}

void Turtle::Up(float _theta){
	x = currx;
	y =curry;
	z = currz;
	theta = ang;

	theta = theta - _theta;
	if(theta > 360){
		theta = theta - 360;
	}

	ang = theta;
	M.makeRotateY(theta);
	M.transpose();

}
void Turtle::down(float _theta){
	x = currx;
	y =curry;
	z = currz;
	theta = ang;
	theta = theta + _theta;
	if(theta > 360){
		theta = theta - 360;
	}

	ang = theta;
	M.makeRotateY(theta);
	M.transpose();

}
void Turtle::dRight(float _theta){

}
void Turtle::dLeft(float _theta){

}


void Turtle::PenDown( bool down )
{
	draw = down;
}

void Turtle::LineColor(float r,float g, float b)
{
	glMatrixMode(GL_MODELVIEW);
	GLfloat red = (GLfloat)r;
	GLfloat green = (GLfloat)g;
	GLfloat blue = (GLfloat)b;
	glColor3f(red, green, blue);
}


void Turtle::BGColor(float r,float g, float b)
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor((GLclampf)r, (GLclampf)g, (GLclampf)b, (GLclampf)0.5);
	glClear(GL_COLOR_BUFFER_BIT);////788908098098
	glFlush();////6897987809809
}

void Turtle::LineWidth( float width )
{
	glLineWidth(width);
}


void Turtle::ResetPosition()
{
	x = 0;
	y = 0;
	theta = 0;
	ang = 0;
	currx = 0;
	curry = 0;
}

void Turtle::ClearScreen()
{
	glMatrixMode(GL_MODELVIEW);
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

}