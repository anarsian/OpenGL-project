#include "robot.h"
//#include "Camera.h"

robot::robot(void)
{
}


robot::~robot(void)
{
}

void robot::drawRobot(double deg, int flag, int translatex, int translatez, Matrix4 cam, int cull)
{
	
	Group* root = new Group();
	Matrix4 identity;
	identity.identity();
	Matrix4 trans;
	trans.makeTranslate(translatex, 7, translatez);
	cam * trans;
	MatrixTransform *m2world = new MatrixTransform(cam);
	cam * m2world->center;
	MatrixTransform *entireRob= new MatrixTransform(identity);

	if(cull == 1)
	{
		root->update(identity);
		Vector3 cent(m2world->center.x, m2world->center.y, m2world->center.z);
	}

	Matrix4 tmp, tmp2, tmp3;

	//Head
	tmp.makeTranslate(0,1.3,-0.2);
	tmp2.makeScale(0.5, 0.375, 0.5);
	tmp * tmp2;
	MatrixTransform head = *new MatrixTransform(tmp);
	head.addChild(new Sphere(0.5, 0.2, 0.0));

	//Body
	tmp.makeScale(1, 0.85, 1);
	MatrixTransform body = *new MatrixTransform(tmp);
	body.addChild(new Sphere(0,0,0));

	//Right arm joint
	tmp2.makeScale(0.1,0.1,0.1);
	tmp.makeTranslate(-1.25, 0.55, -0.2);
	tmp * tmp2;
	Sphere *rjoint = new Sphere(0.5, 0.2, 0.0);
	MatrixTransform rj = *new MatrixTransform(tmp);
	tmp* rjoint->center;
	rj.addChild(rjoint);


	//Right Arm
	tmp2.makeScale(0.2,0.65, 0.4);
	tmp.makeTranslate(-1.25, -0.1, -0.2);
	Vector4 b(rjoint->center.x, 0,0,1);
	tmp3.makeRotate(deg, b);
	tmp * tmp2;
	tmp3 * tmp;
	tmp = tmp3;
	MatrixTransform rarm = *new MatrixTransform(tmp);
	rarm.addChild(new Sphere(0.5, 0.2, 0.0));

	//Left arm joint
	tmp2.makeScale(0.1,0.1,0.1);
	tmp.makeTranslate(1.25, 0.55, -0.2);
	tmp * tmp2;
	Sphere *ljoint = new Sphere(0.5, 0.2, 0.0);
	MatrixTransform lj  = *new MatrixTransform(tmp);
	tmp* ljoint->center;
	lj.addChild(ljoint);

	//Left Arm
	tmp2.makeScale(0.2,0.65, 0.4);
	tmp.makeTranslate(1.25, -0.1, -0.2);
	tmp * tmp2;
	Vector4 a(ljoint->center.x, 0,0,1);
	tmp3.makeRotate(deg, a);
	tmp3 * tmp;
	tmp = tmp3;
	MatrixTransform larm  = *new MatrixTransform(tmp);
	larm.addChild(new Sphere(0.5, 0.2, 0.0));

	//Right leg joint
	tmp2.makeScale(0.01,0.01,0.01);
	tmp.makeTranslate(-0.5, -1, -0.2);
	tmp * tmp2;
	Sphere *jointr = new Sphere(0,0,0);
	MatrixTransform jr = *new MatrixTransform(tmp);
	tmp* jointr->center;
	jr.addChild(jointr);

	//Right leg
	tmp2.makeScale(0.2, 0.7, 0.2);
	tmp.makeTranslate(-0.5, -1.25, -0.2);
	tmp * tmp2;
	Vector4 axis(jointr->center.x, 0,0,1);
	tmp3.makeRotate(-deg, axis);
	tmp3 * tmp;
	tmp = tmp3;
	MatrixTransform rleg = *new MatrixTransform(tmp);
	rleg.addChild(new Sphere(0,0,0));

	//Left leg joint
	tmp2.makeScale(0.01,0.01,0.01);
	tmp.makeTranslate(0.5, -1, -0.2);
	tmp * tmp2;
	Sphere *jointl = new Sphere(0,0,0);
	MatrixTransform jl = *new MatrixTransform(tmp);
	tmp* jointl->center;
	jl.addChild(jointl);

	//Left leg
	tmp2.makeScale(0.2, 0.7, 0.2);
	tmp.makeTranslate(0.5, -1.25, -0.2);
	tmp * tmp2;
	Vector4 axisl(jointl->center.x, 0,0,1);
	tmp3.makeRotate(-deg, axisl);
	tmp3 * tmp;
	tmp = tmp3;
	MatrixTransform lleg = *new MatrixTransform(tmp);

	lleg.addChild(new Sphere(0,0,0));


	//Make heirarchy
	entireRob->addChild(&head);
	entireRob->addChild(&body);
	entireRob->addChild(&rj);
	entireRob->addChild(&rarm);
	entireRob->addChild(&lj);
	entireRob->addChild(&larm);
	entireRob->addChild(&jr);
	entireRob->addChild(&lleg);
	entireRob->addChild(&jl);
	entireRob->addChild(&rleg);
	m2world->addChild(entireRob);
	root->addChild(m2world);


	if(cull == 1)
	{
		root->update(identity);
		Vector3 cent(m2world->center.x, m2world->center.y, m2world->center.z);

		m2world->draw(identity, flag);

	}

	else
	{
		root->update(identity);
		m2world->draw(identity, flag);
	}

}
