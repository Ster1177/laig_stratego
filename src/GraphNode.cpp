#include "GraphNode.h"
#include "appearence.h"
GraphNode::GraphNode() {
	obj = NULL;
	appear = NULL;
	this->children = list<GraphNode *>();
	createIdentityMatrix(transformations);
	display_list =  false;
	xyz[0]=0;
	xyz[1]=0;
	xyz[2]=0;

}

GraphNode::GraphNode(string i, CGFobject * o, appearence *m) {
	id = i;
	obj = o;
	appear = m;
	this->children = list<GraphNode *>();
	createIdentityMatrix(transformations);
	display_list =  false;
	xyz[0]=0;
	xyz[1]=0;
	xyz[2]=0;
}

void GraphNode::setId(string _id){
	id = _id;
}

string GraphNode::getId(){
	return id;
}

void GraphNode::setCGFobject(CGFobject *cgf){
	obj = cgf;
}

CGFobject* GraphNode::getCGFobject(){
	return obj;
}

void GraphNode::addChild( GraphNode * g) {
	this->children.push_back(g);
}

list<GraphNode *>::const_iterator GraphNode::getChildIterator(){
	return children.begin();
}

void GraphNode::setAppearance(appearence* mat){
	appear = mat;
}

appearence* GraphNode::getAppearance() const{
	return appear;
}

bool GraphNode::getDisplayList(){
	return this->display_list;
}

void GraphNode::setDisplayList(bool displ){
	this->display_list = displ;
}

//transformation functions
void GraphNode::translate(double x, double y, double z){
	xyz[0]+=x;
	xyz[1]+=y;
	xyz[2]+=z;
	double *mat = createMatrixTranslate(x,y,z);
	multMatrix( this->transformations, mat);
	delete mat;
}
void GraphNode::scale(double x, double y, double z){
	double *mat = createMatrixScale(x,y,z);
	multMatrix( this->transformations, mat);
	delete mat;
}
void GraphNode::rotate(string eixo, double ang){
	double angle = ang *(3.1475)/180;

	if(eixo == "y") {
		xyz[0] = cos(angle);
		xyz[1] = sin(angle);
	}

	double *mat = createMatrixRotate(eixo,ang);
	multMatrix( this->transformations, mat);
	delete mat;
}



void GraphNode::Orientate(double angle) {
	//translate(-xyz[0],-xyz[1],-xyz[2]);
	double *mat = createMatrixRotate("y",angle);
	multMatrix( this->transformations, mat);
	delete mat;
	//translate(xyz[0],xyz[1],xyz[2]);
}

void GraphNode::draw(){

	glPushMatrix();
		glMultMatrixd(this->transformations);
	if(!this->display_list) {


		if( this->appear != NULL)
			this->appear->apply();


		if( obj != NULL)
			obj->draw();

	}

	list<GraphNode *>::iterator it;
	for(it = children.begin() ; it != children.end() ; it++)
		(*it)->draw();

	glPopMatrix();

}

void GraphNode::displayListDraw(){
	glPushMatrix();

	if(this->display_list) {
		glMultMatrixd(this->transformations);

		if( this->appear != NULL)
			this->appear->apply();


		if(obj != NULL)
			obj->draw();
	}

	list<GraphNode *>::iterator it;
	for(it = children.begin() ; it != children.end() ; it++)
		(*it)->displayListDraw();

	glPopMatrix();
}

GraphNode::~GraphNode() {

}



double* multMatrix(double* m1, double* m2){
	double *mf = new double[16];


	for(int i=0; i< 4; i++){
		for(int j = 0; j < 4; j++)
			mf[i+j*4] = m1[i]*m2[0+j*4] + m1[i+4]*m2[1+j*4] + m1[i+2*4]*m2[2+j*4] + m1[i+3*4]*m2[3+j*4];
	}

	for(int j = 0; j < 16 ; j++)
		m1[j] = mf[j];

	return m1;

}

double* createMatrixTranslate(double x, double y, double z){
	double *mat = new double[16];
	for( int i = 0 ; i < 16; i++){
		if( i%5 == 0)
			mat[i] = 1;
		else
			switch(i) {
			case 12:
				mat[i] = x;
				break;
			case 13:
				mat[i] = y;
				break;
			case 14:
				mat[i] = z;
				break;
			default:
				mat[i]=0.0;
				break;
			}
	}

	return mat;

}

double* createMatrixScale(double x, double y, double z){
	double *mat = new double[16];
	for( int i = 0 ; i < 16; i++){

		switch(i) {
		case 0:
			mat[i] = x;
			break;
		case 5:
			mat[i] = y;
			break;
		case 10:
			mat[i] = z;
			break;
		case 15:
			mat[i] = 1.0;
			break;
		default:
			mat[i]=0.0;
			break;
		}
	}

	return mat;

}


double* createMatrixRotate(string eixo,double rot){
	//M_PI -  180
	//x    -   ang
	double rad = M_PI*rot/180;
	double *mat = new double[16];
	for( int i = 0 ; i < 16; i++){
		if( i%5 == 0)
			mat[i] = 1.0;
		else
			mat[i]=0.0;
	}

	switch(eixo[0]) {
	case 'x':
		/*
		 * 1 0 0 0
		 * 0 cos(rad) -sin(rad) 0
		 * 0 sin(rad) cos(rad) 0
		 * 0 0 0 1
		 */

		mat[5] = cos(rad);
		mat[6] = sin(rad);
		mat[9] = -sin(rad);
		mat[10] = cos(rad);
		break;
	case 'y':
		/*
		 * cos(rad) 0 sin(rad) 0
		 * 0 1 0 0
		 * -sin(rad) 0 cos(rad) 0
		 * 0 0 0 1
		 */

		mat[0] = cos(rad);
		mat[2] = -sin(rad);
		mat[8] = sin(rad);
		mat[10] = cos(rad);
		break;
	case 'z':
		/*
		 * cos(rad) -sin(rad) 0 0
		 * sin(rad) cos(rad) 0 0
		 * 0 0 1 0 0
		 * 0 0 0 0 1
		 */

		mat[0] = cos(rad);
		mat[1] = sin(rad);
		mat[4] = -sin(rad);
		mat[5] = cos(rad);
		break;
	}


	return mat;

}

double* createIdentityMatrix(double* mat){
	for( int i = 0; i < 16 ; i++){
		mat[i] = (i%5 == 0? 1.0 : 0.0);
	}

	return mat;
}












