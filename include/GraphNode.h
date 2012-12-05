#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <list>
#include "cgf/CGFappearance.h"
#include "cgf/CGFobject.h"
#include <cmath>
#include <iostream>
#include "appearence.h"

class GraphNode {
private:
	string id;
	double transformations[16];
	CGFobject * obj;
	appearence * appear;
	list<GraphNode *> children;
	bool display_list;
	double xyz[3];
public:
	GraphNode();
	GraphNode(string, CGFobject * o, appearence * m);

	void setId(string);
	string getId();

	void setCGFobject(CGFobject *);
	CGFobject* getCGFobject();

	void addChild(GraphNode * g);
	list<GraphNode *>::const_iterator getChildIterator();

	void setAppearance(appearence*);
	appearence* getAppearance() const;

	bool getDisplayList();
	void setDisplayList(bool);

	//transformation functions
	void translate(double, double, double);
	void scale(double, double, double);
	void rotate(string,double);
	void Orientate(double);
	void draw();

	void displayListDraw();

	virtual ~GraphNode();
};

//matrix operations
double* multMatrix(double*, double*);
double* createMatrixTranslate(double, double, double);
double* createMatrixScale(double, double, double);
double* createMatrixRotate(string,double);
double* createIdentityMatrix(double*);

#endif /* GRAPHNODE_H_ */
