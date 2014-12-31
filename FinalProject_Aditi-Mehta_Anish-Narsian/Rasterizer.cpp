#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <math.h>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Parser.h"
#include "cube.h"
#include "Camera.h"
#include "House.h"


using namespace std;

static int window_width = 512, window_height = 512;
float* pixels = new float[window_width * window_height * 3];
Parser bunny;
Parser dragon;
Cube bunnyMatrix;
Cube dragonMatrix;
int tag = 1;
Vector4 lightsource (8,60,10, 1);
double intensity = 305;
int lighton = 0;
int zbufferon = 0;
int psizeon = 0;
int sphereon = 0;
float* zbuffer = new float[window_width * window_height * 3];


struct Color    // generic color class
{
	float r,g,b;  // red, green, blue
};

void loadData()
{
	bunny = *new Parser("bunny.xyz", 2);
	dragon = *new Parser("dragon.xyz", 1);
}

// Clear frame buffer
void clearBuffer()
{
	Color clearColor = {0.0, 0.0, 0.0};   // clear color: black
	for (int i=0; i<window_width*window_height; ++i)
	{
		pixels[i*3]   = clearColor.r;
		pixels[i*3+1] = clearColor.g;
		pixels[i*3+2] = clearColor.b;
	}  

	for(int i = 0; i < window_width * window_height * 3; i++)
		zbuffer[i] = 1;

}

// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b, int size)
{
	int t;
	if(size % 2 == 0)
		t = size/2;
	else
		t = (size/2) + 1;
	if (sphereon == 0)
	{
		for(int i = x - size/2; i < x + t; i++)
		{
			for(int j =  y - size/2; j <  y + t; j++)
			{
				int offset = j*window_width*3 + i*3;
				if ((offset + 2) < window_width * window_height * 3 && i < window_width - 2 && j < window_height -2 && offset >= 0)
				{
					pixels[offset] = r;
					pixels[offset + 1] = g;
					pixels[offset + 2] = b;
				}
			}
		}
	}

	else
	{
		for(int i = x - size/2; i < x + t; i++)
		{
			for(int j =  y - size/2; j <  y + t; j++)
			{
				double dx = x - i;
				double dy = y - j;
				double distanceSquared = dx * dx + dy * dy;

				if (distanceSquared <= size*size/4)
				{
					int offset = j*window_width*3 + i*3;
					if ((offset + 2) < window_width * window_height * 3 && i < window_width - 2 && j < window_height -2 && offset >= 0)
					{
						pixels[offset] = r;
						pixels[offset + 1] = g;
						pixels[offset + 2] = b;
					}
				}
			}
		}
	}


}

int getSize (double distance)
{
	int d = floor(distance*10);
	if (d == 8) return 4;
	if (d == 9) return 7;
	if (d > 9) return 9;
	else return (int)(floor(d/2) - 1);
}

void transform(Vector4& tmp, Matrix4& model2world)
{
	double fov = 60 / 180.0 * M_PI;
	double aspect = double(window_width)/(double)window_height;
	double n = 1, f = 1000.0;

	Matrix4 projMatrix;
	projMatrix.m[0][0] = 1.0/(aspect * tan(fov/2));
	projMatrix.m[1][1] = 1.0/tan(fov/2);
	projMatrix.m[2][2] = (n + f) / (n-f);
	projMatrix.m[2][3] = (2.0*n*f)/(n-f);
	projMatrix.m[3][2] = -1;

	Matrix4 cameraMatrix;
	cameraMatrix.makeTranslate(0,0,-20);
	cameraMatrix * model2world;
	projMatrix * cameraMatrix;
	projMatrix * tmp;
	tmp.dehomogenize();
}

void imageSpace(Vector4& tmp)
{
	double x1 = window_width, x0 = 0;
	double y1 = window_height, y0 = 0;
	Matrix4 viewport;
	viewport.identity();
	viewport.m[0][0] = (x1 -x0)/2.0;
	viewport.m[0][3] = (x1 + x0)/2.0;
	viewport.m[1][1] = (y1-y0)/2.0;
	viewport.m[1][3] = (y1+y0)/2.0;
	viewport.m[2][2] = 0.5;
	viewport.m[2][3] = 0.5;
	viewport * tmp;
}

void light(Vector3 pos, Vector3 source, Vector3 normal, Color mc, Color& rc)
{
	Vector3 ld = source - pos;
	double d = ld.length();
	Color li = {1.0*intensity, 1.0*intensity, 1.0*intensity};
	Color lc = {li.r / (d*d), li.g / (d*d), li.b / (d*d) };
	rc.r = 1.0/M_PI * mc.r * lc.r * ld.dot(ld, normal);
	rc.g = 1.0/M_PI * mc.g * lc.g * ld.dot(ld, normal);
	rc.b = 1.0/M_PI * mc.b * lc.b * ld.dot(ld, normal);
}

void rasterize()
{
	if(tag == 1)
	{
		Vector4 tmp3 = lightsource;
		bunnyMatrix.getMatrix() * tmp3;
		Vector3 src (tmp3.x, tmp3.y, tmp3.z);
		for (unsigned int i = 0; i < bunny.vertices.size(); i++)
		{
			Vector4 tmp(bunny.vertices[i].x, bunny.vertices[i].y, bunny.vertices[i].z, 1);
			Vector4 tmp2(bunny.normals[i].x, bunny.normals[i].y, bunny.normals[i].z, 0);
			transform(tmp, bunnyMatrix.getMatrix());
			imageSpace(tmp);
			float zvalue = tmp.z;
			bunnyMatrix.getMatrix() * tmp2;
			if(tmp.x < window_width && tmp.y < window_height && tmp.x > 0 && tmp.y > 0)
			{
				Vector3 pos(tmp.x, tmp.y, tmp.z);
				Vector3 normals(tmp2.x, tmp2.y, tmp2.z);
				Color m = {0.8, 0.1, 1.0};
				Color finalcolor = m;
				if (zbufferon == 1)
				{
					if(zvalue < zbuffer[(int)(floor(tmp.y)*window_width*3 + floor(tmp.x)*3)])
					{
						light(pos, src, normals, m, finalcolor);
						if(psizeon == 1) drawPoint(floor(tmp.x), floor(tmp.y), finalcolor.r, finalcolor.g, finalcolor.b, getSize(zvalue));
						else drawPoint(floor(tmp.x), floor(tmp.y), finalcolor.r, finalcolor.g, finalcolor.b, 1);
						zbuffer[(int)(floor(tmp.y)*window_width*3 + floor(tmp.x)*3)]= zvalue;
					}
				}
				else
				{
					if(lighton == 1) light(pos, src, normals, m, finalcolor);
					drawPoint(floor(tmp.x), floor(tmp.y), finalcolor.r, finalcolor.g, finalcolor.b, 1);
				}
			}

		}
	}

	else
	{
		Vector4 tmp3 = lightsource;
		dragonMatrix.getMatrix() * tmp3;
		Vector3 src (tmp3.x, tmp3.y, tmp3.z);
		for (unsigned int i = 0; i < dragon.vertices.size(); i++)
		{
			Vector4 tmp(dragon.vertices[i].x, dragon.vertices[i].y, dragon.vertices[i].z, 1);
			Vector4 tmp2(dragon.normals[i].x, dragon.normals[i].y, dragon.normals[i].z, 1);
			transform(tmp, dragonMatrix.getMatrix());
			imageSpace(tmp);
			dragonMatrix.getMatrix() * tmp2;
			float zvalue = tmp.z;
			if(tmp.x < window_width && tmp.y < window_height && tmp.x > 0 && tmp.y > 0)
			{
				Vector3 pos(tmp.x, tmp.y, tmp.z);
				Vector3 normals(tmp2.x, tmp2.y, tmp2.z);
				Color m = {0.8, 0.1, 1};
				Color finalcolor = m;
				if (zbufferon == 1)
				{
					if(zvalue < zbuffer[(int)(floor(tmp.y)*window_width*3 + floor(tmp.x)*3)])
					{
						light(pos, src, normals, m, finalcolor);
						if(psizeon == 1) drawPoint(floor(tmp.x), floor(tmp.y), finalcolor.r, finalcolor.g, finalcolor.b, getSize(zvalue));
						else drawPoint(floor(tmp.x), floor(tmp.y), finalcolor.r, finalcolor.g, finalcolor.b, 1);
						zbuffer[(int)(floor(tmp.y)*window_width*3 + floor(tmp.x)*3)]= zvalue;
					}
				}
				else
				{
					if(lighton == 1) light(pos, src, normals, m, finalcolor);
					drawPoint(floor(tmp.x), floor(tmp.y), finalcolor.r, finalcolor.g, finalcolor.b,1);
				}
			}
		}
	}
}

void displayCallback()
{
	clearBuffer();
	rasterize();

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

	glutSwapBuffers();
}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
	cerr << "Window::reshapeCallback called" << endl;
	window_width  = new_width;
	window_height = new_height;
	delete[] pixels;
	pixels = new float[window_width * window_height * 3];
	delete[] zbuffer;
	zbuffer = new float[window_width * window_height * 3];
	bunnyMatrix.reset();
	bunny.findMaxMin();
	bunnyMatrix.moveToCenter(bunny.findCenter());
	bunnyMatrix.makeWindowSize(window_width, bunny.findScaleFactor());
	bunnyMatrix.scale(0.8);
	dragonMatrix.reset();
	dragon.findMaxMin();
	dragonMatrix.moveToCenter(dragon.findCenter());
	dragonMatrix.makeWindowSize(window_width, dragon.findScaleFactor());
	rasterize();
	displayCallback();
}

void keyboardCallback(unsigned char key, int, int)
{
	if(key == 49)
	{
		psizeon = 0;
		zbufferon = 0;
		lighton = 0;
		sphereon = 0;
	}

	if(key == 50)
	{
		psizeon = 0;
		zbufferon = 0;
		lighton = 1;
		sphereon = 0;
	}

	if(key == 51)
	{
		psizeon = 0;
		lighton = 1;
		zbufferon = 1;
		sphereon = 0;
	}

	if(key == 52)
	{
		lighton = 1;
		zbufferon = 1;
		psizeon = 1;
		sphereon = 0;
	}

	if (key == 53)
	{
		lighton = 1;
		zbufferon = 1;
		psizeon = 1;
		sphereon = 1;
	}

	//if x is pressed, move cube left
	if (key == 120)
	{
		if(tag == 1) bunnyMatrix.translate(-0.9,0,0);
		if(tag == 2) dragonMatrix.translate(-0.9,0,0);
		displayCallback();
	}

	//if X is pressed, move cube right
	if (key == 88)
	{
		if(tag == 1) bunnyMatrix.translate(0.9,0,0);
		if(tag == 2) dragonMatrix.translate(0.9,0,0);
		displayCallback();
	}

	//if y is pressed, move cube down
	if (key == 121)
	{
		if(tag == 1) bunnyMatrix.translate(0,-0.9,0);
		if(tag == 2) dragonMatrix.translate(0,-0.9,0);
		displayCallback();
	}

	//if Y is pressed, move cube up
	if (key == 89)
	{
		if(tag == 1) bunnyMatrix.translate(0,0.9,0);
		if(tag == 2) dragonMatrix.translate(0,0.9,0);
		displayCallback();
	}

	//move cube into the screen by a small amount
	if (key == 122)
	{
		if(tag == 1) bunnyMatrix.translate(0,0,-0.9);
		if(tag == 2) dragonMatrix.translate(0,0,-0.9);
		displayCallback();
	}

	//move cube out of the screen by a small amount
	if (key == 90)
	{
		if(tag == 1) bunnyMatrix.translate(0,0,0.9);
		if(tag == 2) dragonMatrix.translate(0,0,0.9);
		displayCallback();
	}

	//reset
	if(key == 114)
	{
		if(tag == 1) bunnyMatrix.reset();
		if(tag == 2) dragonMatrix.reset();
		displayCallback();
	}

	//scale down
	if(key == 115)
	{
		if(tag == 1) bunnyMatrix.scale(0.95);
		if(tag == 2) dragonMatrix.scale(0.95);
		displayCallback();
	}

	//scale up
	if(key == 83)
	{
		if(tag == 1) bunnyMatrix.scale(1.05);
		if(tag == 2) dragonMatrix.scale(1.05);
		displayCallback();
	}

	//rotate right and left
	if(key == 113)
	{
		if(tag == 1) bunnyMatrix.spin(15);
		if(tag == 2) dragonMatrix.spin(15);
		displayCallback();
	}

	if(key == 81)
	{
		if(tag == 1) bunnyMatrix.spin(-15);
		if(tag == 2) dragonMatrix.spin(-15);
		displayCallback();
	}

}

void specialKeyCallback(int key, int, int)
{
	if(key == GLUT_KEY_F1)
	{
		bunnyMatrix.reset();
		bunny.findMaxMin();
		bunnyMatrix.moveToCenter(bunny.findCenter());
		bunnyMatrix.makeWindowSize(window_width, bunny.findScaleFactor());
		bunnyMatrix.scale(0.8);
		bunnyMatrix.translate(0.8,0,0);
		tag = 1;
		displayCallback();
	}

	if(key == GLUT_KEY_F2)
	{
		dragonMatrix.reset();
		dragon.findMaxMin();
		dragonMatrix.moveToCenter(dragon.findCenter());
		dragonMatrix.makeWindowSize(window_width, dragon.findScaleFactor());
		tag = 2;
		displayCallback();
	}

}

void idleCallback()
{
	displayCallback();
}

int main_tp(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Rasterizer");

	loadData();

	glutReshapeFunc(reshapeCallback);
	glutDisplayFunc(displayCallback);
	glutIdleFunc(idleCallback);
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(specialKeyCallback);

	bunnyMatrix.getMatrix().identity();
	dragonMatrix.getMatrix().identity();
	glutMainLoop();

	return 0;
}
