#include "Patch.h"
#include <sstream>

//+step[2],+type
Patch::Patch(int*st,string tp) {

	this->stepu = st[0];
	this->stepv = st[0];
	this->order = 3;

	if(tp == "fill")
		this->type = GL_FILL;
	else if(tp == "point")
		this->type = GL_POINT;
	else
		this->type = GL_LINE;

	init();

}

Patch::Patch(elem* ec){

//	<patch partsU=”ii” partsV=”ii” compute=”ss”>
//	  <controlpoint x=”ff” y=”ff” z=”ff” />
	this->order = 3;
	stringstream *ss = new stringstream(ec->attr["partsU"]);
	*ss >> this->stepu;
	delete ss;

	ss = new stringstream(ec->attr["partsV"]);
	*ss >> this->stepv;
	delete ss;

	if(ec->attr["compute"] == "fill")
		this->type = GL_FILL;
	else if(ec->attr["compute"] == "point")
		this->type = GL_POINT;
	else
		this->type = GL_LINE;

	init();
}


void Patch::init(){
	GLfloat grid4x4[4][4][3] =
	{
		{
			{2.0, -2.0, 0.0},
			{0.5, -2.0, 0.0},
			{-0.5, -2.0, 0.0},
			{-2.0, -2.0, 0.0}},
		{
			{2.0, -0.5, 0.0},
			{0.5, -0.5,  -1.0},
			{-0.5, -0.5, -1.0},
			{-2.0, -0.5, 0.0}},
		{
			{2.0, 0.5, 0.0},
			{0.5, 0.5, -1.0},
			{-0.5, 0.5, -1.0},
			{-2.0, 0.5, 0.0}},
		{
			{2.0, 2.0,  0.0},
			{0.5, 2.0,  0.0},
			{-0.5, 2.0, 0.0},
			{-2.0, 2.0, 0.0}}
	};


	int n = (3+1)*(3+1)*3;

	GLfloat* ct = new GLfloat[n];
	GLfloat* temp = &(grid4x4[0][0][0]);
	for(int k = 0; k < n ; k++)
		ct[k] = temp[k];

	this->ctrlpoints = ct;
}

void Patch::draw(){

	glPushMatrix();
//		glColor3f(1.0,1.0,1.0);
		glEnable(GL_AUTO_NORMAL);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, this->order+1,
				0.0, 1.0, (this->order+1)*3, this->order+1,(const GLfloat*)  ctrlpoints);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(this->stepu, 0.0,1.0, this->stepv, 0.0,1.0);
		glEvalMesh2(this->type, 0,this->stepu, 0,this->stepv);
	glPopMatrix();
}
