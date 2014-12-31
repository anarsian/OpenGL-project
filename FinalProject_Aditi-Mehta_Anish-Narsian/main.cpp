#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "shader.h"
#include <GL/glut.h>


#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Camera.h"
#include "main.h"
#include "textfile.h"
using namespace std;

namespace Globals
{
	Cube patchMatrix;
	Matrix4 lightMatrix;
	Cube spotMatrix;
	Shader* shader;
	Shader* plantshader;
	Bezier patch;
	int twidth[6], theight[6];   // texture width/height [pixels]
	unsigned char* tdata[6];  // texture pixel data
	GLuint texture[6];     // storage for one texture
	GLuint* tex_cube;
	Particle particle_Array[600];
	Grammar gr;
};

int main(int argc, char *argv[])
{
	float specular[]  = {0.0, 0.0, 0.0, 0.0};
	float shininess[] = {0.0};

	glutInit(&argc, argv);      	      	      // initialize GLUT

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
	glutInitWindowSize(Window::width, Window::height);      // set initial window size
	glutCreateWindow("Final Project");    	      // open window and set window title


	// Install callback functions:
	glutDisplayFunc(Window::displayCallback);
	glutReshapeFunc(Window::reshapeCallback);
	glutIdleFunc(Window::idleCallback);
	glutKeyboardFunc(Window::processNormalKeys);

	glEnable(GL_TEXTURE_2D);   // enable texture mapping
	glShadeModel(GL_SMOOTH);   // enable smooth shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // black background
	glClearDepth(1.0f);        // depth buffer setup
	glEnable(GL_DEPTH_TEST);   // enables depth testing
	glDepthFunc(GL_LEQUAL);    // configure depth testing
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   

	glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glEnable(GL_CULL_FACE);     // enable backface culling to render both sides of polygons
	glCullFace(GL_BACK); 
	//glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION); 

	// Generate material properties:
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Initialize matrices:
	Window::initializePoints(0);
	Globals::patchMatrix.getMatrix().identity();
	Globals::patchMatrix.translate(0, -2, 18);
	Globals::spotMatrix.getMatrix().identity();
	Globals::spotMatrix.translate(0,-2,18);
	Globals::shader = new Shader("shade.vert", "shade.frag");
	Globals::plantshader = new Shader("shade.vert", "shade2.frag");
	Window::lightOn();
	Window::loadTexture(-1);
	Window::initializeParticles();
	Globals::gr.grow3();
	glutMainLoop();
	return 0;
}



