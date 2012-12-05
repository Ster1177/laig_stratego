
#include "primitives.h"
#include <sstream>
#include <cmath>
using namespace std;




//ESFERA
Sphere::Sphere(double r, int sl, int st){
	radius = r;
	slices = sl;
	stacks = st;
	quadratic = gluNewQuadric();

}

Sphere::Sphere(elem* el){
	stringstream* ss;


	ss = new stringstream( el->attr["radius"]);
	*ss >> this->radius;
	delete ss;

	ss = new stringstream( el->attr["slices"]);
	*ss >> this->slices;
	delete ss;

	ss = new stringstream( el->attr["stacks"]);
	*ss >> this->stacks;
	delete ss;

	quadratic = gluNewQuadric();

	delete el;

}

double Sphere::getRadius() const
{
	return radius;
}

int Sphere::getSlices() const
{
	return slices;
}

int Sphere::getStacks() const
{
	return stacks;
}

void Sphere::setRadius(double r)
{
	radius = r;
}

void Sphere::setSlices(int sl)
{
	slices = sl;
}

void Sphere::setStacks(int st)
{
	stacks = st;
}

void Sphere::draw()
{
    gluQuadricTexture(quadratic, GL_TRUE);      // Create Texture Coords
    gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals
	gluSphere(quadratic, radius, slices, stacks);
}

//CILINDRO
Cylinder::Cylinder(double br, double tr, double ht, int sl, int st)
{

	baseRadius = br;
	topRadius = tr;
	height = ht;
	slices = sl;
	stacks = st;
	quadratic = gluNewQuadric();
	quadratic_base = gluNewQuadric();


}
Cylinder::Cylinder(elem* el){
	//<cylinder base="1" top="1" height="1" slices="50" stacks="50" />
	stringstream* ss;

	ss = new stringstream( el->attr["base"] ); *ss >> this->baseRadius; delete ss;
	ss = new stringstream( el->attr["height"] ); *ss >> this->height; delete ss;
	ss = new stringstream( el->attr["top"] ); *ss >> this->topRadius; delete ss;
	ss = new stringstream( el->attr["slices"] ); *ss >> this->slices; delete ss;
	ss = new stringstream( el->attr["stacks"] ); *ss >> this->stacks; delete ss;

	delete el;


	quadratic = gluNewQuadric();
	quadratic_base = gluNewQuadric();
}

double Cylinder::getBaseradius() const
{
	return baseRadius;
}

double Cylinder::getTopradius() const
{
	return topRadius;
}
double Cylinder::getHeight() const
{
	return height;
}
int Cylinder::getSlices() const
{
	return slices;
}

int Cylinder::getStacks() const
{
	return stacks;
}

void Cylinder::setTopradius(double tr)
{
	topRadius = tr;
}

void Cylinder::setBaseradius(double br)
{
	baseRadius = br;
}

void Cylinder::setHeight(double ht)
{
	height = ht;
}

void Cylinder::setSlices(int sl)
{
	slices = sl;
}

void Cylinder::setStacks(int st)
{
	stacks = st;
}

void Cylinder::draw()
{

	gluQuadricTexture(quadratic, GL_TRUE);      // Create Texture Coords
	gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals
	gluCylinder(quadratic, baseRadius, topRadius, height, slices, stacks);



	//bottom
	glPushMatrix();
		glRotated(180,0,1,0);
		gluDisk(quadratic_base,0,baseRadius,slices,stacks);
	glPopMatrix();

	//top
	glPushMatrix();
		glTranslated(0,0,height);
		gluDisk(quadratic_base,0,topRadius,slices,stacks);
	glPopMatrix();
}

//RECTANGULO
Rectangle::Rectangle(double x_1, double y_1, double x_2, double y_2)
{

	x1 = x_1;
	x2 = x_2;
	y1 = y_1;
	y2 = y_2;
}

Rectangle::Rectangle(elem* el){
	//<rectangle x1="0" y1="0" x2="1" y2="1" />
	stringstream* ss;

	ss = new stringstream( el->attr["x1"] ); *ss >> this->x1; delete ss;
	ss = new stringstream( el->attr["y1"] ); *ss >> this->y1; delete ss;
	ss = new stringstream( el->attr["x2"] ); *ss >> this->x2; delete ss;
	ss = new stringstream( el->attr["y2"] ); *ss >> this->y2; delete ss;

	delete el;
}

double Rectangle::getX1() const
{
	return x1;
}

double Rectangle::getX2() const
{
	return x2;
}

double Rectangle::getY1() const
{
	return y1;
}

double Rectangle::getY2() const
{
	return y2;
}

void Rectangle::setX1(double x_1)
{
	x1 = x_1;
}

void Rectangle::setX2(double x_2)
{
	x2 = x_2;
}

void Rectangle::setY1(double y_1)
{
	y1 = y_1;
}

void Rectangle::setY2(double y_2)
{
	y2 = y_2;
}

void Rectangle::draw()
{
	//normal is the same for all
		//a = [x1,y1,0], b = [x1,y2,0], c = [x2,y1,0]
		//ab = {0, y2-y1, 0};
		//ac = {x2 - x1, 0, 0};
		//normal = ab X ac

	double normal[] = {0 ,0 , (y2-y1)*(x2-x1)};

	//normalize
	normal[2] /= sqrt(normal[2]*normal[2]);

	glBegin(GL_QUADS);
		glNormal3d(normal[0],normal[1],normal[2]);
		glVertex3d(x1,y1,0);
		glNormal3d(normal[0],normal[1],normal[2]);
		glVertex3d(x2,y1,0);
		glNormal3d(normal[0],normal[1],normal[2]);
		glVertex3d(x2,y2,0);
		glNormal3d(normal[0],normal[1],normal[2]);
		glVertex3d(x1,y2,0);
	glEnd();
}

//TRIANGULO
Triangle::Triangle(double x_1, double y_1, double z_1, double x_2, double y_2, double z_2,
		double x_3, double y_3, double z_3)
{

	x1 = x_1;y1 = y_1;z1 = z_1;
	x2 = x_2;y2 = y_2;z2 = z_2;
	x3 = x_3;y3 = y_3;z3 = z_3;
}

Triangle::Triangle(elem* el) {
	//<triangle x1="0" y1="0" z1="0" x2="1" y2="0" z2="0" x3="0.5" y3="1" z3="0" />
	stringstream *ss;


	ss = new stringstream( el->attr["x1"] );
	*ss >> x1;
	delete ss;

	ss = new stringstream( el->attr["y1"] );
	*ss >> y1;
	delete ss;

	ss = new stringstream( el->attr["z1"] );
	*ss >> z1;
	delete ss;

	ss = new stringstream( el->attr["x2"] );
	*ss >> x2;
	delete ss;

	ss = new stringstream( el->attr["x2"] );
	*ss >> y2;
	delete ss;

	ss = new stringstream( el->attr["z2"] );
	*ss >> z2;
	delete ss;

	ss = new stringstream( el->attr["x3"] );
	*ss >> x3;
	delete ss;

	ss = new stringstream( el->attr["y3"] );
	*ss >> y3;
	delete ss;

	ss = new stringstream( el->attr["z3"] );
	*ss >> z3;
	delete ss;



	delete el;
}

double Triangle::getX1() const
{
	return x1;
}

double Triangle::getX2() const
{
	return x2;
}

double Triangle::getX3() const
{
	return x3;
}

double Triangle::getY1() const
{
	return y1;
}

double Triangle::getY2() const
{
	return y2;
}

void Triangle::setX1(double x_1)
{
	x1 = x_1;
}

void Triangle::setX2(double x_2)
{
	x2 = x_2;
}

void Triangle::setX3(double x_3)
{
	x3 = x_3;
}

void Triangle::setY1(double y_1)
{
	y1 = y_1;
}

void Triangle::setY2(double y_2)
{
	y2 = y_2;
}

void Triangle::setY3(double y_3)
{
	y3 = y_3;
}

void Triangle::setZ1(double z_1)
{
	z1 = z_1;
}

void Triangle::setZ2(double z_2)
{
	z2 = z_2;
}

void Triangle::setZ3(double z_3)
{
	z3 = z_3;
}

void Triangle::draw()
{
	double normal[3];

	//normal is the same for all
		//a = [x1, y1,z1], b = [x2,y2,z2], c = [x3,y3,z3]
		//ba = {x1 - x2, y1 - y2, z1 - z2};
		//bc = {x3 - x2, y3 - y2, z3 - z2};
		//normal = ab X ac
	normal[0] = (y3-y2)*(z2-z1) - (z3-z2)*(y1-y2);
	normal[1] = (z3-z2)*(x1-x2) - (x3-x2)*(z1-z2);
	normal[2] = (x3-x2)*(y1-y2) - (y3-y2)*(x1-x2);
	double normalize_factor = sqrt( normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
	//normalize
	normal[0] /= normalize_factor;
	normal[1] /= normalize_factor;
	normal[2] /= normalize_factor;

	glBegin(GL_TRIANGLES);
		glNormal3d(normal[0], normal[1], normal[2]);
		glVertex3d(x1,y1,z1);
		glNormal3d(normal[0], normal[1], normal[2]);
		glVertex3d(x2,y2,z2);
		glNormal3d(normal[0], normal[1], normal[2]);
		glVertex3d(x3,y3,z3);
	glEnd();

}
//TORUS
Torus::Torus(double inR, double outR, int sl, int lp)
{

	innerRadius = inR;
	outerRadius = outR;
	slices = sl;
	loops = lp;
}

Torus::Torus(elem* el){
    //<torus inner="0.5" outer="1" slices="80" loops="10" />
	stringstream* ss;

	ss = new stringstream(  el->attr["inner"] ); *ss >> this->innerRadius; delete ss;
	ss = new stringstream(  el->attr["outer"] ); *ss >> this->outerRadius; delete ss;
	ss = new stringstream(  el->attr["slices"] ); *ss >> this->slices; delete ss;
	ss = new stringstream(  el->attr["loops"] ); *ss >> this->loops; delete ss;

	delete el;
}

double Torus::getInnerRadius() const
{
	return innerRadius;
}

double Torus::getOuterRadius() const
{
	return outerRadius;
}

int Torus::getSlices() const
{
	return slices;
}

int Torus::getLoops() const
{
	return loops;
}

void Torus::setInnerRadius(double inR)
{
	innerRadius = inR;
}

void Torus::setOuterRadius(double outR)
{
	outerRadius = outR;
}

void Torus::setSlices(int sl)
{
	slices = sl;
}

void Torus::setLoops(int lp)
{
	loops = lp;
}

void Torus::draw()
{
	glutSolidTorus(innerRadius,outerRadius,slices,loops);
}
