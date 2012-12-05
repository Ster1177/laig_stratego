/*
 * Patch.h
 */

#ifndef PATCH_H_
#define PATCH_H_
#include <iostream>
#include <string>
#include "cgf/CGFobject.h"
#include "parser.h"

using namespace std;

class Patch : public CGFobject{
private:
	GLuint stepu;
	GLuint stepv;
	GLuint order;
	int type; // fill, line, point...
	GLfloat* ctrlpoints;
	GLfloat* nrmlcompon;

	void init_points();
public:
	Patch();

	//+step[2],+types
	Patch(int*,string);
	Patch(elem*);


	void init();
	void draw();
	~Patch(){};
};

#endif /* PATCH_H_ */
