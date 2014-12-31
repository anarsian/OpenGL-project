#include <iostream>

#include <GLee.h>
#include <Glee.c>

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "shader.h"
#include "grammar.h"
#include "robot.h"

using namespace std;
int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
int drawOn = -1;
int exampleNum = 0;
int rob = -1;

int flag = -1;
double t = 0.0, q= 0.0;
Vector4 corner1, corner2, corner3, corner4;
int pcount = 600;
int water = -1;
int c = 1;

void Window::idleCallback()
{
	displayCallback();         // call display routine to show the cube
}

void Window::reshapeCallback(int w, int h)
{
	cerr << "Window::reshapeCallback called" << endl;
	width = w;
	height = h;
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
	glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glMatrixMode(GL_MODELVIEW);
}

void Window::displayCallback()
{
	glEnable(GL_NORMALIZE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);
	Matrix4 tmp = Globals::patchMatrix.getMatrix();
	tmp.transpose();
	glLoadMatrixd(tmp.getPointer());
	glColor3f(0.6, 0.3, 0.0);

	if (flag == 1) Globals::shader->bind();

	glBegin(GL_QUADS);
	for(int i = 0; i < 99; i++)
	{
		for(int j = 0; j < 99; j++)
		{
			glNormal3f(Globals::patch.normals[i][j].x, Globals::patch.normals[i][j].y, Globals::patch.normals[i][j].z);
			glVertex3f(Globals::patch.vertices[i][j].x, 0, Globals::patch.vertices[i][j].z);

			glNormal3f(Globals::patch.normals[i][j+1].x, Globals::patch.normals[i][j+1].y, Globals::patch.normals[i][j+1].z);
			glVertex3f(Globals::patch.vertices[i][j+1].x, 0, Globals::patch.vertices[i][j+1].z);

			glNormal3f(Globals::patch.normals[i+1][j+1].x, Globals::patch.normals[i+1][j+1].y, Globals::patch.normals[i+1][j+1].z);
			glVertex3f(Globals::patch.vertices[i+1][j+1].x, 0, Globals::patch.vertices[i+1][j+1].z);

			glNormal3f(Globals::patch.normals[i+1][j].x, Globals::patch.normals[i+1][j].y, Globals::patch.normals[i+1][j].z);
			glVertex3f(Globals::patch.vertices[i+1][j].x, 0, Globals::patch.vertices[i+1][j].z);
		}
	}
	glEnd();
	if (flag == 1) Globals::shader->unbind();


	glMatrixMode(GL_MODELVIEW);
	tmp = Globals::spotMatrix.getMatrix();
	tmp.transpose();
	glLoadMatrixd(tmp.getPointer());
	glColor3f(0.0, 0.8, 0.0);
	//DRAW TREE!!!!!!!
	if(flag == 1) Globals::plantshader->bind();
	if (drawOn == 1)
	{
		//printf("here");
		q += 1;
		if(q == 2.0 && c < 7) 
		{
			Globals::gr.grow();
			q = 0.0;
			c++;
		}
	}

	Globals::gr.render(c);
	if(flag == 1) Globals::plantshader->unbind();


	glMatrixMode(GL_MODELVIEW);
	tmp = Globals::patchMatrix.getMatrix();
	tmp.transpose();
	glLoadMatrixd(tmp.getPointer());
	if(water == 1)
	{
		updateParticles();
		drawParticles();
	}

	//RIGHT
	loadTexture(3);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(corner2.x, corner2.y, corner2.z);
	glTexCoord2f(1, 1);
	glVertex3f(corner1.x, corner1.y, corner1.z);
	glTexCoord2f(1, 0);
	glVertex3f(corner1.x, 5, corner1.z);
	glTexCoord2f(0, 0);
	glVertex3f(corner2.x, 5, corner2.z);
	glEnd();

	//BACK
	loadTexture(1);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(corner3.x, corner3.y, corner2.z);
	glTexCoord2f(1, 1);
	glVertex3f(corner2.x, corner2.y, corner2.z);
	glTexCoord2f(1, 0);
	glVertex3f(corner2.x, 5, corner2.z);
	glTexCoord2f(0, 0);
	glVertex3f(corner3.x, 5, corner3.z);
	glEnd();

	//LEFT
	loadTexture(4);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(corner4.x, corner4.y, corner4.z);
	glTexCoord2f(1, 1);
	glVertex3f(corner3.x, corner3.y, corner3.z);
	glTexCoord2f(1, 0);
	glVertex3f(corner3.x, 5, corner3.z);
	glTexCoord2f(0, 0);
	glVertex3f(corner4.x, 5, corner4.z);
	glEnd();


	//TOP

	glDisable(GL_CULL_FACE);
	loadTexture(0);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(corner4.x,5, corner4.z);
	glTexCoord2f(1, 1);
	glVertex3f(corner1.x, 5, corner1.z);
	glTexCoord2f(1, 0);
	glVertex3f(corner2.x, 5, corner2.z);
	glTexCoord2f(0, 0);
	glVertex3f(corner3.x, 5, corner3.z);
	glEnd();

	//TOP - TOP
	loadTexture(2);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(corner4.x,10, corner4.z);
	glTexCoord2f(1, 1);
	glVertex3f(corner1.x, 10, corner1.z);
	glTexCoord2f(1, 0);
	glVertex3f(corner2.x, 10, corner2.z);
	glTexCoord2f(0, 0);
	glVertex3f(corner3.x, 10, corner3.z);
	glEnd();

	//TOP - BACK
	loadTexture(5);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(corner3.x, 5, corner2.z);
	glTexCoord2f(1, 1);
	glVertex3f(corner2.x, 5, corner2.z);
	glTexCoord2f(1, 0);
	glVertex3f(corner2.x, 10, corner2.z);
	glTexCoord2f(0, 0);
	glVertex3f(corner3.x, 10, corner3.z);
	glEnd();


	//TOP - LEFT
	loadTexture(5);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(corner4.x, 5, corner4.z);
	glTexCoord2f(1, 1);
	glVertex3f(corner3.x, 5, corner3.z);
	glTexCoord2f(1, 0);
	glVertex3f(corner3.x, 10, corner3.z);
	glTexCoord2f(0, 0);
	glVertex3f(corner4.x, 10, corner4.z);
	glEnd();

	//TOP - RIGHT
	loadTexture(5);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(corner2.x, 5, corner2.z);
	glTexCoord2f(1, 1);
	glVertex3f(corner1.x, 5, corner1.z);
	glTexCoord2f(1, 0);
	glVertex3f(corner1.x, 10, corner1.z);
	glTexCoord2f(0, 0);
	glVertex3f(corner2.x, 10, corner2.z);
	glEnd();
	if(rob == 1)
	{
		robot r;
		r.drawRobot(0, 0, 1, -1, Globals::patchMatrix.getMatrix(), 0); 
	}

	glFlush();  
	glutSwapBuffers();
}

void Window::processNormalKeys(unsigned char key, int x, int y) 
{
	if(key == 'g')
	{
		Globals::gr.randomVal = (rand() % 5) * 0.015;
		while(Globals::gr.randomVal == 0)
			Globals::gr.randomVal = (rand() % 5) * 0.015;
	}
	if (key == 90)
	{
		glMatrixMode(GL_PROJECTION);
		glTranslatef(0, 0, 0.9); 
		glMatrixMode(GL_MODELVIEW);
	}

	if (key == 122)
	{
		glMatrixMode(GL_PROJECTION);
		glTranslatef(0, 0, -0.9); 
		glMatrixMode(GL_MODELVIEW);
	}

	if(key == 'X')
	{
		glMatrixMode(GL_PROJECTION);
		glTranslatef(0.9, 0, 0); 
		glMatrixMode(GL_MODELVIEW);
	}

	if(key == 'x')
	{
		glMatrixMode(GL_PROJECTION);
		glTranslatef(-0.9, 0, 0); 
		glMatrixMode(GL_MODELVIEW);
	}


	if (key == 89)
	{
		glMatrixMode(GL_PROJECTION);
		glTranslatef(0, 0.9, 0); 
		glMatrixMode(GL_MODELVIEW);
	}

	if (key == 121)
	{
		glMatrixMode(GL_PROJECTION);
		glTranslatef(0, -0.9, 0); 
		glMatrixMode(GL_MODELVIEW);
	}

	if(key == 't')
		flag *= -1;

	if(key == 'l')
	{
		Globals::patchMatrix.spin(5);
	}

	if(key == 'L')
		Globals::patchMatrix.spin(-5);

	if(key == 'p')
		Globals::patchMatrix.spinx(5);

	if(key == 'P')
		Globals::patchMatrix.spinx(-5);

	if(key == 'e')
		Globals::spotMatrix.spin(5);
	if(key == 'E')
		Globals::spotMatrix.spin(-5);

	if(key == 'r')
		water *= -1;

	if(key == 'd')
	{
		drawOn *= -1;
	}

	if(key == 'R')
		rob *= -1;


}

void Window::initializePoints(double t)
{
	Globals::patch.points[0] = *new Vector4(4,0,4,0);
	Globals::patch.points[1] = *new Vector4(2,0,2,0);
	Globals::patch.points[2] = *new Vector4(-2,0,4,0);
	Globals::patch.points[3] = *new Vector4(-4,0,4,0);
	Globals::patch.points[4] = *new Vector4(4,0,2,0);
	Globals::patch.points[5] = *new Vector4(2,0,2,0);
	Globals::patch.points[6] = *new Vector4(-2,0,2,0);
	Globals::patch.points[7] = *new Vector4(-4,0,2,0);
	Globals::patch.points[8] = *new Vector4(4,0,-2,0);
	Globals::patch.points[9] = *new Vector4(2,0,-2,0);
	Globals::patch.points[10] = *new Vector4(-2,0,-2,0);
	Globals::patch.points[11] = *new Vector4(-4,0,-2,0);
	Globals::patch.points[12] = *new Vector4(4,0,-4,0);
	Globals::patch.points[13] = *new Vector4(2,0,-4,0);
	Globals::patch.points[14] = *new Vector4(-2,0,-4,0);
	Globals::patch.points[15] = *new Vector4(-4,0,-4,0);

	Globals::patch.createPatchStuff();

	corner1 = Globals::patch.vertices[0][0];
	corner2 = Globals::patch.vertices[0][99];
	corner3 = Globals::patch.vertices[99][99];
	corner4 = Globals::patch.vertices[99][0];
}

unsigned char* Window::loadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ( (fp=fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width  = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}

void Window::loadTexture(int i)
{
	// Load image file
	if(i == -1)
	{
		Globals::tdata[0] = loadPPM("top.ppm", Globals::twidth[0], Globals::theight[0]);
		if (Globals::tdata[0]==NULL) return;
		glGenTextures(1, &Globals::texture[0]);   

		Globals::tdata[1] = loadPPM("back.ppm", Globals::twidth[1], Globals::theight[1]);
		if (Globals::tdata[1]==NULL) return;
		glGenTextures(1, &Globals::texture[1]); 

		Globals::tdata[2] = loadPPM("tops.ppm", Globals::twidth[2], Globals::theight[2]);
		if (Globals::tdata[2]==NULL) return;
		glGenTextures(1, &Globals::texture[2]);

		Globals::tdata[3] = loadPPM("right.ppm", Globals::twidth[3], Globals::theight[3]);
		if (Globals::tdata[3]==NULL) return;
		glGenTextures(1, &Globals::texture[3]); 

		Globals::tdata[4] = loadPPM("left.ppm", Globals::twidth[4], Globals::theight[4]);
		if (Globals::tdata[4]==NULL) return;
		glGenTextures(1, &Globals::texture[4]); 

		Globals::tdata[5] = loadPPM("tops2.ppm", Globals::twidth[5], Globals::theight[5]);
		if (Globals::tdata[5]==NULL) return;
		glGenTextures(1, &Globals::texture[5]); 
	}

	else
	{

		//glGenTextures(i+1, &Globals::texture[i]);
		glBindTexture(GL_TEXTURE_2D, Globals::texture[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Globals::twidth[i], Globals::theight[i], 0, GL_RGB, GL_UNSIGNED_BYTE, Globals::tdata[i]);
		//Set bi-linear filtering for both minification and magnification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

}

void Window::lightOn()
{
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	Matrix4 tmp = Globals::patchMatrix.getMatrix();
	tmp.transpose();
	glLoadMatrixd(tmp.getPointer());
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat position[] = {3.5, 0.5,-2.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHT0); 

	GLfloat position1[] = {2.5, 3 ,0.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, diffuse);

	glEnable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void Window::initializeParticles()
{

	int i;
	for (i = 1; i < pcount; i++)
	{
		Globals::particle_Array[i].Xpos = rand()%6 + ((rand()%100) *0.01) + ((rand() %10) *0.1) -3;
		Globals::particle_Array[i].Ypos = 2.0 + (i%100)*0.3 + ((rand()%100) *0.01) + ((rand() %10) *0.1);
		Globals::particle_Array[i].Zpos = 2.0 + (i%100)*0.2 + ((rand()%100) *0.01) + ((rand() %10) *0.1);
		Globals::particle_Array[i].Xmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) *
			rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1
			) * rand()%11) + 1) * 0.005);
		Globals::particle_Array[i].Zmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) *
			rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1
			) * rand()%11) + 1) * 0.005);
		Globals::particle_Array[i].Deceleration = 0.2;
	}

}

void Window::updateParticles()
{

	int i;
	for (i = 1; i < pcount; i++)
	{

		Globals::particle_Array[i].Ypos = Globals::particle_Array[i].Ypos - Globals::particle_Array[i].Deceleration;
		Globals::particle_Array[i].Deceleration = Globals::particle_Array[i].Deceleration +
			0.0075;

		Globals::particle_Array[i].Xpos = Globals::particle_Array[i].Xpos + Globals::particle_Array[i].Xmov;
		Globals::particle_Array[i].Zpos = Globals::particle_Array[i].Zpos + Globals::particle_Array[i].Zmov;


		if (Globals::particle_Array[i].Ypos < 0)
		{
			Globals::particle_Array[i].Xpos =  rand()%6 + ((rand()%100) *0.01) + ((rand() %10) *0.1) -3;
			Globals::particle_Array[i].Ypos = 2.0 + (i%100)*0.3 + ((rand()%100) *0.01) + ((rand() %10) *0.1);
			Globals::particle_Array[i].Zpos = 0;
			Globals::particle_Array[i].Deceleration = 0.2;
		}

	}

}

void Window::drawParticles()
{
	glColor3f (0.0, 0.0, 0.05);
	glBegin(GL_QUADS); 
	int i;
	for (i = 1; i < pcount; i++)
	{
		if(Globals::particle_Array[i].Ypos > 5)
			continue;
		glVertex3f(Globals::particle_Array[i].Xpos - 0.005, Globals::particle_Array[i].Ypos - 0.025,Globals::particle_Array[i].Zpos);
		glVertex3f(Globals::particle_Array[i].Xpos + 0.005, Globals::particle_Array[i].Ypos - 0.025,Globals::particle_Array[i].Zpos);
		glVertex3f(Globals::particle_Array[i].Xpos + 0.005, Globals::particle_Array[i].Ypos + 0.025,Globals::particle_Array[i].Zpos);
		glVertex3f(Globals::particle_Array[i].Xpos - 0.005, Globals::particle_Array[i].Ypos + 0.025,Globals::particle_Array[i].Zpos);
	}
	glEnd();
}



