//
//  grammar.cpp
//  Final Project
//
//  Created by anish Narsian on 12/10/14.
//  Copyright (c) 2014 Anish Narsian. All rights reserved.
//

#include "grammar.h"
#include <GL/GLUT.h>


#include <math.h>
#include "Turtle.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>




Grammar::Grammar() {
	//str = "F";
	str = "I";
	//structure.push_back(pos);
	//drawLine
	randomVal = (rand() % 5) * 0.025;
	dist_length = 0.002;

}

void Grammar::grow3() {
	//std::string a;
	
	for(int i = 0; i<5; i++) {
	std::string a;
	for(int i = 0; i< str.length(); i++) {
	if(strncmp(&str[i], "I", 1) == 0) {
	//str.replace(i, 1, "R[ABC][ABC]R");
	// a+="F[RFC][LFC]F";
	//a+= "FF-[-F+F+F]+[+F-F-F]";
	//a+= "F-[[X]+X]+F[+FX]-X";
	//a+= "FF-[-F+F+F]+[+F-F-F]";
	a+="VZFFF";

	}
	else if(strncmp(&str[i], "V", 1) == 0) {
	a+="[+++W][---W]YV";
	}
	else if(strncmp(&str[i], "W", 1) == 0) {
	a+="+X[-W]Z";
	}
	else if(strncmp(&str[i], "X", 1) == 0) {
	a+="-W[+X][Z]";
	}
	else if(strncmp(&str[i], "Y", 1) == 0) {
	a+="YZ";
	}
	else if(strncmp(&str[i], "Z", 1) == 0) {
	a+="[-FFF][+FFF]F";
	}
	else if(strncmp(&str[i], "F", 1) == 0) {
	a+="F";
	}

	else
	a+=str[i];
	}
	str = a;
	}
	//str = a;

	
}

void Grammar::grow() {
	//srand(time(NULL));
	std::string a;
	for(int i = 0; i< str.length(); i++) {
	if(strncmp(&str[i], "I", 1) == 0) {
	//str.replace(i, 1, "R[ABC][ABC]R");
	// a+="F[RFC][LFC]F";
	//a+= "FF-[-F+F+F]+[+F-F-F]";
	//a+= "F-[[X]+X]+F[+FX]-X";
	//a+= "FF-[-F+F+F]+[+F-F-F]";
	a+="VZFFF";

	}
	else if(strncmp(&str[i], "V", 1) == 0) {
	a+="[+++W][---W]YV";
	}
	else if(strncmp(&str[i], "W", 1) == 0) {
	a+="+X[-W]Z";
	}
	else if(strncmp(&str[i], "X", 1) == 0) {
	a+="-W[+X][Z]";
	}
	else if(strncmp(&str[i], "Y", 1) == 0) {
	a+="YZ";
	}
	else if(strncmp(&str[i], "Z", 1) == 0) {
	a+="[-FFF][+FFF]F";
	}
	else if(strncmp(&str[i], "F", 1) == 0) {
	a+="F";
	}

	else
	a+=str[i];
	}
	str = a;
	dist_length = 1.5 * dist_length;
	
}





void Grammar::render(float dist) {
	//glMatrixMode(GL_MODELVIEW);
	//str = "A";
	// trt.ClearScreen();
	trt.Init(-0.1, 0.1
		, -0.2, 90);		// Move to the center (facing right)
	//trt.BGColor(0, 0, 0);		// Set Background color black
	// trt.LineColor(0, 1, 0);
	for(int i =0; i<str.length(); i++) {
		if(strncmp(&str[i],"F",1) == 0 ){//|| strncmp(&str[i],"F",1) == 0 ) {
			//srand(time(NULL));
			// dist_length = rand()%25; 
			//std::cout<< "dist input: " << dist;
			trt.Forward(dist * randomVal);
			if(trt.currx>maxX) maxX = trt.currx;
			if(trt.currx<minX) minX = trt.currx;

			if(trt.curry>maxY) maxY = trt.curry;
			if(trt.curry<minY) minY = trt.curry;

			if(trt.currz>maxZ)maxZ =trt.currz;
			if(trt.currz<minZ)minZ =trt.currz;

		}
		else if(strncmp(&str[i],"[",1) == 0 ) {
			//glPushMatrix();
			st.push(Vector4(trt.currx, trt.curry, trt.currz, trt.ang));

		}
		else if(strncmp(&str[i],"]",1) == 0 ) {
			Vector4 v = st.top();
			trt.currx = v.x;
			trt.curry = v.y;
			trt.currz = v.z;
			trt.ang = v.w;
			st.pop();


		}
		else if(strncmp(&str[i],"+",1) == 0 ) {

			trt.Up(22.5);
		}
		else if(strncmp(&str[i],"-",1) == 0 ) {
			trt.down(22.5);
		}


	}
	/* double len = 0.005;
	for(int i =0; i<str.length(); i++) {
	if(strncmp(&str[i],"F",1) == 0) {
	//line
	line(structure[i].v3[0], structure[i].v3[1], structure[i].v3[2]);


	}
	else if(strncmp(&str[i],"[",1) == 0) {
	glPushMatrix();
	}
	else if(strncmp(&str[i],"]",1) == 0) {
	glPopMatrix();
	}
	else if(strncmp(&str[i],"R",1) == 0) {
	rotRight();
	}
	else if(strncmp(&str[i],"C",1) == 0) {
	makeChild();
	}
	else if(strncmp(&str[i],"L",1) == 0) {
	rotLeft();
	}
	else {}
	}*/
}













