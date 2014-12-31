//
//  Turtle.h
//  Final Project
//
//  Created by anish Narsian on 12/14/14.
//  Copyright (c) 2014 Anish Narsian. All rights reserved.
//

#ifndef __Final_Project__Turtle__
#define __Final_Project__Turtle__

#include <stdio.h>
#include <stack>
#include "Matrix4.h"


class Turtle{
    
public:
   /* double minX;
    double minY;
    double minZ;
    double maxX;
    double maxY;
    double maxZ;*/
    
    Matrix4 M;
    float currx;
    float curry;
    float currz;
    float ang;
    Vector4 H;
    Vector4 L;
    Vector4 U;
    Vector4 wComp;
    Matrix4 tMat;
    void rotateH(double a);
    void rotateL(double a);
    void rotateU(double a);
    

    Turtle();
   // std::stack<Turtle> sta;
    
    

void Init(float _x,float _y, float _z, float _theta);
void Forward(float dist);
void Backward(float dist);
void Right(float _theta);
void Left(float _theta);
void Up(float _theta);
void down(float _theta);
void dRight(float _theta);
void dLeft(float _theta);
void PenDown ( bool down );
void LineColor(float r,float g, float b);
void BGColor(float r,float g, float b);
void LineWidth( float width );
void ResetPosition();
void ClearScreen();

void initCanvas(int size);
    };

#endif /* defined(__Final_Project__Turtle__) */
