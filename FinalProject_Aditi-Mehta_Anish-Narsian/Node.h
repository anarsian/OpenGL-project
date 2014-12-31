#ifndef _NODE_H_
#define _NODE_H_

#include "Matrix4.h"
#include <list>
#include <GL\glut.h>

class Node
{
public:
	double radius;
	Vector4 center;
	Node(void){}
	~Node(void){}
	virtual void draw(Matrix4 C, int flag) = 0;
	virtual void update(Matrix4 C) = 0;

};

class Group :
	public Node
{
public:
	std::list<Node*> children;
	Group()
	{
		radius = 1;
		center.x = 0;
		center.y = 0;
		center.z = 0;
		center.w = 1;
	}
	~Group()
	{
		children.clear();
	}
	void addChild(Node* child)
	{
		children.push_back(child);
	}
	void removeChild(Node* child)
	{
		children.remove(child);
	}

	void Node::draw(Matrix4 C, int flag)
	{
		if(flag == 1) 
		{
			update(C);
			glColor3f(1,0,0);
			glutWireSphere(radius, 5, 5);
		}
		for (std::list<Node*>::iterator it=children.begin(); it != children.end(); ++it)
		{
			(*it)->draw(C, flag);
		}
	}
	void Node::update(Matrix4 C)
	{
		C * center;
		Vector4 tmp(radius, radius, radius, 0);
		Vector4 sample = center + tmp; 
		C * sample;
		Vector4 tmp2 = center - sample;
		this->radius = sqrt(tmp.x*tmp.x+tmp.y*tmp.y+tmp.z*tmp.z);
		
		for (std::list<Node*>::iterator it=children.begin(); it != children.end(); ++it)
		{
			(*it)->update(C);
		}
	}

};

class Geode :
	public Node
{
public:
	void Node::draw(Matrix4 C, int flag) 
	{
		glMatrixMode(GL_MODELVIEW);
		C.transpose();
		glLoadMatrixd(C.getPointer());
		render(flag);
	}

	virtual void render(int flag) = 0;
};

class MatrixTransform : public Group
{
public:
	Matrix4 M;
	MatrixTransform(Matrix4 m)
	{
		M = m;
		radius = 1;
		center.x = 0;
		center.y = 0;
		center.z = 0;
		center.w = 1;
	}
	~MatrixTransform(void)
	{}

	void Node::draw(Matrix4 C, int flag)
	{
		C * M;
		M = C;
		for (std::list<Node*>::iterator it=children.begin(); it != children.end(); ++it)
		{
			(*it)->draw(C, flag);
		}
		if(flag == 1) 
		{
			update(C);
			glColor3f(1,0,0);
			glutWireSphere(radius, 5, 5);
		}
	}

	void Node::update(Matrix4 C)
	{
		C * center;
		Vector4 tmp(radius, radius, radius, 0);
		Vector4 sample = center + tmp; 
		C * sample;
		Vector4 tmp2 = center - sample;
		
		this->radius = sqrt(tmp.x*tmp.x+tmp.y*tmp.y+tmp.z*tmp.z);
		
		for (std::list<Node*>::iterator it=children.begin(); it != children.end(); ++it)
		{
			(*it)->update(C);
		}
		
	}


};

class Sphere : public Geode
{
public:
	double rc, gc, bc;
	Sphere(double r, double g, double b)
	{
		radius = 1;
		center.x = 0;
		center.y = 0;
		center.z = 0;
		center.w = 1;
		rc = r;
		gc = g;
		bc = b;

	}
	void Geode::render(int flag)
	{

		glColor3f(rc,gc,bc);
		glutSolidSphere(1,50,50);
		if(flag == 1) 
		{
			glColor3f(1,0,0);
			glutWireSphere(radius, 5, 5);
		}
	}

	void Node::update(Matrix4 C)
	{
	}

};



#endif