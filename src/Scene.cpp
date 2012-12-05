#include "Scene.h"
#include "cgf/CGFaxis.h"
#include "cgf/CGFapplication.h"
#include "primitives.h"
#include "Patch.h"
#include "parser.h"
#include "RotateAnimation.h"
#include <sstream>
#include <list>
#include <math.h>
#include "cgf/CGFappearance.h"

//Animation objects declaration


unsigned int pos = 0;
unsigned int size = 0;


Scene::Scene(Elems* globals,elemContainer* lconfig):lights(), cameras(), cam(0), light(1){
	Elems::iterator it = globals->begin();
	cullEnabled = false;
	graph = NULL;

	//GLOBAL STUFF

	for(; it != globals->end() ; it++){
		if( (*it)->name == "background" ){
			//<background r="0" g="0" b="0" a="0" />
			stringstream ss;
			ss << (*it)->attr["r"]; ss >> background[0];
			ss << (*it)->attr["g"]; ss >> background[1];
			ss << (*it)->attr["b"]; ss >> background[2];
			ss << (*it)->attr["a"]; ss >> background[3];

		} else if( (*it)->name == "polygon" ){
			//<polygon mode="fill" shading="gouraud" />
			polygMode = (*it)->attr["mode"];
			polygShading = (*it)->attr["shading"];

		} else if( (*it)->name == "culling" ){
	        //<culling frontfaceorder="CW" cullface="both" enabled="false" />
			frontFaceOrder = (*it)->attr["frontfaceorder"];
			cullFace = (*it)->attr["cullface"];
			cullEnabled = ((*it)->attr["enabled"] == "true" ? true : false);
		}

		//won't be needed anymore
		delete *it;
	}

	delete globals;

	//LIGHTING CONFIG STUFF
	//root	   <lighting doublesided="false" local="true" enabled="true" >
	//	  elems:     <ambient r="1" g="1" b="1" a="0" />
	if( lconfig->root->attr["doublesided"] == "true" )
		this->doublesided = true;
	else
		this->doublesided = false;

	if( lconfig->root->attr["local"] == "true" )
		this->local = true;
	else
		this->local = false;

	if( lconfig->root->attr["enabled"] == "true" )
		this->enabled = true;
	else
		this->enabled = false;

	for( it = lconfig->elems->begin() ; it != lconfig->elems->end() ; it++ )
		if((*it)->name == "ambient"){
			stringstream ss;
			ss << (*it)->attr["r"]; ss >> this->ambient[0];
			ss << (*it)->attr["g"]; ss >> this->ambient[1];
			ss << (*it)->attr["b"]; ss >> this->ambient[2];
			ss << (*it)->attr["a"]; ss >> this->ambient[3];
			break;
		}

}


void Scene::addLight(Light *light){
	this->lights.push_back(light);
}

//includes adding cgfobgjects
void Scene::setGraph(Graph* gr){
	graph = gr;
}

void Scene::addCGFcamera(Cameras* cam){
	this->cameras.push_back(cam);
	//TODO set active camera
}





void Scene::init()
{

	int mode = (polygMode == "fill" ? GL_FILL : 0);

	if(mode == 0)
		mode = (polygMode == "line" ? GL_LINE : 0);
	if(mode == 0)
		mode = (polygMode == "point" ? GL_POINT : 0);


	//CULLING AND POLYGON MODES
	if(cullEnabled){

		glEnable(GL_CULL_FACE);

		if( cullFace == "both" || cullFace == "front"){

			if( cullFace == "both"){

				glCullFace(GL_FRONT_AND_BACK);
				glPolygonMode(GL_FRONT_AND_BACK, mode);

			} else if(cullFace == "front" ) {

				glCullFace(GL_FRONT);
				glPolygonMode(GL_FRONT, mode);
			}
			if( frontFaceOrder == "CCW")
				glFrontFace(GL_CCW);
			else
				glFrontFace(GL_CW);

		}else {
			glCullFace(GL_BACK);
			glPolygonMode(GL_BACK, mode);
		}
	}

	// Enables lighting computations
	glEnable(GL_LIGHTING);

	//Lighting Config!!
	if(this->doublesided)
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	else
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	if( this->local)
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	else
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->ambient);  // Define ambient light



	if(polygShading == "gouraud")
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);

	list<Light *>::iterator light_it = lights.begin();
	for(int i = 0; (light_it != lights.end()) && (i < 8) ; light_it++)
		if( (*light_it)->isEnabled() ){
			(*light_it)->init();
			i++;
		}

	Animation * anim;
	Animation * anim1;
	Animation * anim2;
	Animation * anim3;
	anims = new PolyLineAnimation();
	//compiles the display list!
	this->display_list = glGenLists(1);
	glNewList(this->display_list,GL_COMPILE);
	this->graph->getRoot()->displayListDraw();
	glEndList();


	RotateAnimation * rot;
	this->setUpdatePeriod(10);
	temp = new GraphNode("cylinder",new Cylinder(1,1,1,50,50), NULL);
	temp->translate(40,4,40);

//	anim = new LineAnimation(0,0,0,0,10,10,temp,5);
//	rot = new RotateAnimation(temp, 3, 90);
//	anims->addAnimation(rot);

	anim1 = new LineAnimation(0,10,10, 10,10,10,temp,5);
	anim2 = new LineAnimation(10,10,10,10,10,3,temp,5);
	anim3 = new LineAnimation(10,10,3,2,4,3,temp,5);


	//Add the animations to apply
//	anims->addAnimation(anim);
	anims->addAnimation(anim1);
	anims->addAnimation(anim2);
	anims->addAnimation(anim3);

//	anims->addAnimation(rot);
	//Get size of animations' vector
	size = anims->getAnimations().size();


	elem * e = new elem;
	e->name = "terrain";
//	<terrain heightmap="textures/HuntersTown.png" texturemap="textures/HuntersTown_tex.jpg" fragmentshader="shaders/terrain.frag" vertexshader="shaders/terrain.vert" />
	e->attr["heightmap"] = "textures/HuntersTown.png";
	e->attr["texturemap"] = "textures/HuntersTown_tex.jpg";
	e->attr["fragmentshader"] = "shaders/terrain.frag";
	e->attr["vertexshader"] = "shaders/terrain.vert";



	terr = new Terrain(e);
}

void Scene::update(long t){
	cout << "Last update: " << t << endl;
//	cout << "Size: " << size << endl;
	if(anims->getAnimations()[pos]->end == true){
		if (pos < size-1)
		{
			pos++;cout << "next animation " << pos ;
			anims->getAnimations()[pos]->time = t;
		}
	}

	 anims->getAnimations()[pos]->updateTime(t);

}
void Scene::display()
{
	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin

	if(this->cam > cameras.size())
		this->cam = 0;
	int i = this->cam;
	list<Cameras *>::iterator it;
	if(i != 0){
		for( it = cameras.begin() ; it != cameras.end() ;it++)
			if(--i == 0){
				(*it)->updateProjectionMatrix(CGFapplication::vpw, CGFapplication::vph);
				(*it)->applyView();
			}
	} else{
		CGFscene::activeCamera->applyView();

	}

	if(light == lights.size() )
		light =0;
	//draw lights: only 8 at the most
	list<Light *>::iterator light_it = lights.begin();
	for(int i = 0; (light_it != lights.end()) && (i < 8) ; light_it++){
		if(light == 1)
			(*light_it)->setEnabled(true);
		else
			(*light_it)->setEnabled(false);
		(*light_it)->draw();
		i++;
	}


	// Draw axis
	axis.draw();


	temp->draw();

	terr->draw();



	//draw Display list!0
	glCallList(this->display_list);


	//TODO DRAW OBJECTS AND SHIT
	if(graph != NULL)
	{
		graph->getRoot()->draw();
	}

	// We have been drawing in a memory area that is not visible - the back buffer,
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();

}

Scene::~Scene()
{

}
