#ifndef _MAIN_H_
#define _MAIN_H_

#include "Cube.h"
#include "Camera.h"
#include "Parser.h"
#include "shader.h"
#include "Bezier.h"
#include "grammar.h"

typedef struct
{
double Xpos;
double Ypos;
double Zpos;
double Xmov;
double Zmov;
double Deceleration;
}Particle;


namespace Globals
{
    extern Cube patchMatrix;
	extern Matrix4 lightMatrix;
	extern Cube spotMatrix;
	extern Shader *shader;
	extern Shader *plantshader;
	extern Bezier patch;
	extern int twidth[6], theight[6];   // texture width/height [pixels]
	extern unsigned char* tdata[6];  // texture pixel data
	extern GLuint texture[6];     // storage for one texture
	extern GLuint* tex_cube;
	extern Particle particle_Array[600];
	extern Grammar gr;
};


#endif