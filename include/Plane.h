#ifndef PLANE_H_
#define PLANE_H_

#include <iostream>
#include <string>
#include "cgf/CGFobject.h"
#include "parser.h"


using namespace std;

class Plane: public CGFobject {
private:
	GLuint step;
	GLfloat ctrlpoints[4][3];
	GLfloat nrmlcompon[4][3];
	GLfloat colorpoints[4][4];
	GLfloat texpoints[4][2];

	void init_points();
public:
	Plane();
	Plane(int);
	Plane(elem*);

	void init();
	void draw();
	~Plane(){};
};

#endif /* PLANE_H_ */
