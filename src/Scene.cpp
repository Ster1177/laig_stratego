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
		if( (*it)->name == "background"){
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

	selected_piece = map<GLuint,Piece *>();
	not_selected_piece = map<GLuint,Piece *>();
	pieces = map<GLuint,Piece *>();
	choices = pair<bool, pair<GLuint,GLuint> >();
	b = new Board();
	//One piece
	Piece * peca;
	for(unsigned int i=1; i<=10; i++) {
		peca = new Piece();
		pieces[i]= peca;
//		not_selected_piece[i] = peca;
	}
	choices.first = false;
	choices.second = pair<GLuint,GLuint>();

}

void Scene::update(long t){

	// if something is selected
	if(choices.first) {
		//if piece was selected before
		if(choices.second.first == 0) {
			//Se for > 0, destino foi seleccionado
			if(choices.second.second > 0) {
			 //TODO: mover peça
				choices.first = false;

			}
		}
		else {
			//popular maps
			//criar lists gl_compile
			choices.second.first = 0;
		}
	}

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
			//	(*it)->updateProjectionMatrix(CGFapplication::vpw, CGFapplication::vph);
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
	b->draw();



	// picking example, the important parts are the gl*Name functions
		// and the code in the associted PickInterface class

	// Example 1: simple naming
		glPushMatrix();
		glPushName(-1);		// Load a default name

		for (int i=0; i< NUM_OBJS;i++)
		{
			glPushMatrix();
			glTranslatef(i*1.4,0,0);
			glLoadName(i);		//replaces the value on top of the name stack
			glCallList(1);
			glPopMatrix();
		}

		glPopMatrix();


	// We have been drawing in a memory area that is not visible - the back buffer,
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();

}


Scene::~Scene()
{

}
