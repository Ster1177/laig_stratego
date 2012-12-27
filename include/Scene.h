#ifndef SCENE_H
#define SCENE_H
#include "Shader.h"
#include "cgf/CGFscene.h"
#include "cgf/CGFshader.h"
#include "cgf/CGFtexture.h"
#include "parser.h"
#include "Plane.h"
#include "Patch.h"
#include "Graph.h"
#include "Light.h"
#include "Cameras.h"
#include "PolyLineAnimation.h"
#include "Board.h"
#include "Piece.h"
#include <utility>
//#include "PickInterface.h"

#define NUM_OBJS 3
#define NUM_ROWS 10
#define NUM_COLS 10

class Scene : public CGFscene
{
	//friend PickInterface;
public:
//globals
	float background[4];
	//polygon
	string polygMode;
	string polygShading;
	//culling
	string frontFaceOrder;
	string cullFace;
	bool cullEnabled;

//lighting config
	bool doublesided;
	bool local;
	bool enabled;
	float ambient[4];

	list<Light *> lights;
	CGFlight* light0;

	Graph *graph;
	list<Cameras *> cameras;

	//display list in use
	GLuint display_list;
	pair<bool,pair<GLuint,GLuint>> choices;
	map<GLuint,Piece *> selected_piece;
	map<GLuint,Piece *> not_selected_piece;
	map<GLuint, Piece *> pieces;

	Terrain * terr;
	Board * b;

	GraphNode* temp;
	PolyLineAnimation * anims;

	//params: globals, lightingconfig
	Scene(Elems*,elemContainer*);
	void addLight(Light *);
	//includes adding cgfobgjects
	void setGraph(Graph *);
	void addCGFcamera(Cameras*);

	void init();
	void display();
	void update(long t);
	virtual ~Scene();
	int cam;
	int light;


};

#endif
