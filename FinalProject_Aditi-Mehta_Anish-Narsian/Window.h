#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Vector3.h"
#include <vector>

class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	            // window size

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void processNormalKeys(unsigned char key, int x, int y);
	static void initializePoints(double t);
	static unsigned char* loadPPM(const char* filename, int& width, int& height);
	static void loadTexture(int);
	static void lightOn();
	static void initializeParticles();
	static void updateParticles();
	static void drawParticles();
	
};

#endif

