//
//  grammar.h
//  Final Project
//
//  Created by anish Narsian on 12/10/14.
//  Copyright (c) 2014 Anish Narsian. All rights reserved.
//

#ifndef __Final_Project__grammar__
#define __Final_Project__grammar__

#include <stdio.h>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Turtle.h"
#include <stack>
#include "Vector4.h"

class Grammar {
    
public:
    
    double minX;
    double minY;
    double minZ;
    double maxX;
    double maxY;
    double maxZ;
    Turtle trt;
    std::stack<Vector4> st;
	float randomVal, dist_length;
    //std::vector<Vector3> structure;
    std::string str;
    Grammar();
    void grow();
    void grow3();
    void render(float dist);
    void line(double x, double y, double z);
    void rotRight();
    void rotLeft();
    void makeChild();
    
};

#endif /* defined(__Final_Project__grammar__) */
